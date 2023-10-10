import {
    CharStream,
    CommonTokenStream,
    ErrorListener,
    ParserRuleContext,
    ParseTree,
    TerminalNode,
    Token,
} from 'antlr4';
import ScriptGrammarLexer from './ScriptGrammarLexer.ts';
import ScriptGrammarParser, {
    AccessExpressionContext,
    ArgumentsContext,
    BlockStatementContext,
    BreakStatementContext,
    ClassDeclarationContext,
    ContinueStatementContext,
    ElseStatementContext,
    ExpressionContext,
    ForStatementContext,
    FunctionDeclarationContext,
    IfStatementContext,
    MemberContext,
    MembersContext,
    MultiIfStatementContext,
    ParamsContext,
    ReturnStatementContext,
    StatementsContext,
    VariableDeclarationContext,
    WhileStatementContext
} from './ScriptGrammarParser.ts';
import {Recognizer} from "antlr4/src/antlr4/Recognizer";
import {RecognitionException} from "antlr4/src/antlr4/error/RecognitionException";
import {
    AssignmentExpression,
    BinaryExpression,
    BlockStatement,
    BreakStatement,
    CallExpression,
    ClassDeclaration,
    ContinueStatement,
    Declaration,
    DynamicMemberExpression,
    Expression,
    ForeachStatement,
    ForStatement,
    FunctionDeclaration,
    Identifier,
    IfStatement,
    Literal,
    LoopStatement,
    MemberExpression,
    NewExpression,
    Program,
    ReturnStatement,
    Statement,
    UnaryExpression,
    VariableDeclaration,
    WhileStatement
} from "./psi.ts";

export class ScriptGrammarErrorListener extends ErrorListener<Token> {
    syntaxError(recognizer: Recognizer<Token>, offendingSymbol: Token, line: number, column: number, msg: string, e: RecognitionException | undefined): void {
        throw new Error(`program:${line}:${column}: error: ${msg}`)
    }
}

export class ASTBuilder {
    private _ASTJson: Program = null

    psi() { return this._ASTJson }

    compile(input: string) {
        const chars = new CharStream(input);
        const lexer = new ScriptGrammarLexer(chars);
        const tokens = new CommonTokenStream(lexer);
        const parser = new ScriptGrammarParser(tokens);
        parser.removeErrorListeners()
        parser.addErrorListener(new ScriptGrammarErrorListener())
        try {
            const tree = parser.program();
            this._ASTJson = this.handleProgram(tree)
        } catch (e) {
            console.error(e)
        }
    }

    handleProgram(program: ParseTree) {
        const prog = new Program().loc(this.location(program))
        this.handleParseTree(program,
                tree => {
                    if (tree instanceof ClassDeclarationContext) {
                        const identifiers = this.findTerminals(tree.children, ScriptGrammarLexer.ID)
                        const classDeclaration = new ClassDeclaration()
                        classDeclaration.id = this.handleIdentifier(identifiers[0])
                        this.unfoldMembers(this.findFirstParserRule(tree.children, ScriptGrammarParser.RULE_members))
                            .forEach(member =>
                                member instanceof VariableDeclaration
                                    ? classDeclaration.variables.push(member)
                                    : classDeclaration.methods.push(member as FunctionDeclaration)
                            )
                        prog.body.push(classDeclaration)
                        return true
                    }
                    if (tree instanceof VariableDeclarationContext) {
                        prog.body.push(this.handleVariableDeclaration(tree))
                        return true
                    }
                    if (tree instanceof FunctionDeclarationContext) {
                        prog.body.push(this.handleFunctionDeclaration(tree))
                        return true
                    }
                    return false
                },
                tree => {}
            )
        prog.body.forEach(d => d.relate(prog))
        return prog
    }

    handleMember(tree: MemberContext): Declaration {
        if (tree.children[0] instanceof VariableDeclarationContext)
            return this.handleVariableDeclaration(tree.children[0])
        if (tree.children[0] instanceof FunctionDeclarationContext)
            return this.handleFunctionDeclaration(tree.children[0])
    }

    handleVariableDeclaration(tree: VariableDeclarationContext): VariableDeclaration {
        const v = new VariableDeclaration().loc(this.location(tree))
        v.id = this.handleIdentifier(tree.children[0] as TerminalNode)
        v.init = this.handleExpression(tree.children[2] as ExpressionContext)
        return v
    }

    handleFunctionDeclaration(tree: FunctionDeclarationContext): FunctionDeclaration {
        const params = this.findFirstParserRule(tree.children, ScriptGrammarParser.RULE_params)
        const f = new FunctionDeclaration().loc(this.location(tree))
        f.id = this.handleIdentifier(tree.children[1] as TerminalNode)
        f.params = (params !== null ? this.unfoldParams(params) : []).map(p => p.relate(f))
        f.body = this.handleBlockStatement(tree.children[tree.children.length - 1] as BlockStatementContext)
        return f
    }

    handleStatements(tree: StatementsContext): Array<Statement> {
        return this.unfoldStatements(tree);
    }

    handleIfStatement(tree: IfStatementContext): IfStatement {
        const conditions =
            this.unfoldMultiIfStatement(tree.children[0] as MultiIfStatementContext)
        let index = 1
        let iter = conditions[0]
        while (index < conditions.length) {
            // conditions[index].relate(iter)
            iter.alternate = conditions[index]
            iter = conditions[index]
            index++
        }
        const elseStatement = tree.children[1] as ElseStatementContext
        if (elseStatement.children.length > 0)
            conditions[conditions.length - 1].alternate =
                this.handleBlockStatement(elseStatement.children[1] as BlockStatementContext)
        return conditions[0].loc(this.location(tree))
    }

    handleForStatement(tree: ForStatementContext): LoopStatement {
        const semi = this.indexOfTerminals(tree.children, ScriptGrammarLexer.SEMI)
        const isNumeric = semi.length > 0
        if (isNumeric) {
            const l = new ForStatement().loc(this.location(tree))
            l.init = tree.children[semi[0] - 1] instanceof ExpressionContext
                ? this.handleExpression(tree.children[semi[0] - 1] as ExpressionContext) : null
            l.test = tree.children[semi[1] - 1] instanceof ExpressionContext
                ? this.handleExpression(tree.children[semi[1] - 1] as ExpressionContext) : null
            l.update = tree.children[semi[2] - 1] instanceof ExpressionContext
                ? this.handleExpression(tree.children[semi[2] - 1] as ExpressionContext) : null
            l.body = this.handleBlockStatement(tree.children[tree.children.length - 1] as BlockStatementContext)
            // l.init?.relate(l); l.test?.relate(l); l.update?.relate(l); l.body.relate(l)
            return l
        } else {
            const l = new ForeachStatement().loc(this.location(tree))
            l.left  = this.handleExpression(tree.children[2] as ExpressionContext)
            l.right = this.handleExpression(tree.children[4] as ExpressionContext)
            l.body  = this.handleBlockStatement(tree.children[tree.children.length - 1] as BlockStatementContext)
            // l.left.relate(l); l.right.relate(l); l.body.relate(l)
            return l
        }
    }

    handleWhileStatement(tree: WhileStatementContext): WhileStatement {
        const w = new WhileStatement().loc(this.location(tree))
        w.test = this.handleExpression(tree.children[2] as ExpressionContext)
        w.body = this.handleBlockStatement(tree.children[4] as BlockStatementContext)
        // w.test.relate(w); w.body.relate(w)
        return w
    }

    handleReturnStatement(tree: ReturnStatementContext): ReturnStatement {
        const r = new ReturnStatement().loc(this.location(tree))
        r.argument = tree.children.length === 2 ? this.handleExpression(tree.children[1] as ExpressionContext) : null
        // r.argument?.relate(r)
        return r
    }

    handleContinueStatement(tree: ContinueStatementContext): ContinueStatement {
        return new ContinueStatement().loc(this.location(tree))
    }

    handleBreakStatement(tree: BreakStatementContext): BreakStatement {
        return new BreakStatement().loc(this.location(tree))
    }

    handleBlockStatement(tree: BlockStatementContext): BlockStatement {
        const b = new BlockStatement().loc(this.location(tree))
        b.body = tree.children.length === 3 ? this.handleStatements(tree.children[1] as StatementsContext) : []
        b.body.forEach(s => s.relate(b))
        return b
    }

    handleExpression(tree: ExpressionContext): Expression {
        if (tree.children[0] instanceof TerminalNode && tree.children[0].getText() === '(') {
            let obj: Expression = this.handleExpression(tree.children[1] as ExpressionContext)
            const last = tree.children[tree.children.length - 1] as any
            if (last.ruleIndex && last.ruleIndex === ScriptGrammarParser.RULE_accessExpression) {
                obj = this.handleAccessExpression(obj, last)
            }
            return obj.loc(this.location(tree))
        }
        if (tree.children[0] instanceof TerminalNode && tree.children[0].getText() === 'new') {
            let obj = this.handleNewExpression(tree.children[1] as TerminalNode, [])
            const last = tree.children[tree.children.length - 1] as any
            if (last.ruleIndex && last.ruleIndex === ScriptGrammarParser.RULE_accessExpression) {
                obj = this.handleAccessExpression(obj, last)
            }
            return obj.loc(this.location(tree))
        }
        if (tree.children[0] instanceof TerminalNode && tree.children[0].symbol.type === ScriptGrammarLexer.ID) {
            let obj = this.handleIdentifier(tree.children[0])
            const last = tree.children[tree.children.length - 1] as any
            if (last.ruleIndex && last.ruleIndex === ScriptGrammarParser.RULE_accessExpression) {
                obj = this.handleAccessExpression(obj, last)
            }
            return obj.loc(this.location(tree))
        }
        if (tree.children.length === 1) { return this.handleTerminal(tree.children[0] as TerminalNode) }
        if (tree.children.length === 2
            && tree.children[0] instanceof TerminalNode
            && tree.children[1] instanceof ExpressionContext) {
            return this.handleUnaryExpression(tree.children[0], tree.children[1]).loc(this.location(tree))
        }
        if (tree.children.length === 2
            && tree.children[0] instanceof ExpressionContext
            && tree.children[1] instanceof TerminalNode) {
            return this.handleUnaryExpression(tree.children[1], tree.children[0], false).loc(this.location(tree))
        }
        if (tree.children.length === 3
            && tree.children[0] instanceof ExpressionContext
            && tree.children[1] instanceof TerminalNode
            && tree.children[2] instanceof ExpressionContext
        ) {
            return tree.children[1].getText() === '='
                ? this.handleAssignmentExpression(tree.children[0], tree.children[2]).loc(this.location(tree))
                : this.handleBinaryExpression(tree.children[1], tree.children[0], tree.children[2]).loc(this.location(tree))
        }
        return null
    }

    handleAccessExpression(obj, tree: AccessExpressionContext) {
        const seq = this.unfoldAccessExpression(tree)
        let index = 0
        let iObj = obj
        while (index < seq.length) {
            seq[index].relate(iObj)
            if (seq[index] instanceof CallExpression) {
                (seq[index] as CallExpression).callee = iObj
            } else {
                (seq[index] as MemberExpression).object_ = iObj
            }
            // if (Object.hasOwn(seq[index], "callee")) {
            //     (seq[index] as any).callee  = iObj
            // } else {
            //     (seq[index] as any).object_ = iObj
            // }
            iObj = seq[index]
            index++
        }
        return iObj
    }

    handleMemberExpression(obj, id: TerminalNode) {
        const call = new MemberExpression()
        call.object_ = obj//.relate(call)
        call.property = this.handleIdentifier(id)//.relate(call)
        return call
    }

    handleDynamicMemberExpression(obj, expr: ExpressionContext) {
        const call = new DynamicMemberExpression()
        call.object_ = obj//?.relate(call)
        call.property = this.handleExpression(expr)//.relate(call)
        return call
    }

    handleCallExpression(obj, args: ArgumentsContext) {
        const call = new CallExpression()
        call.callee = obj//?.relate(call)
        call.arguments = this.unfoldArguments(args).map(a => a.relate(call))
        return call
    }

    handleNewExpression(callee: TerminalNode, _arguments: Array<ExpressionContext>) {
        const newObj = new NewExpression()
        newObj.callee = this.handleIdentifier(callee)//.relate(newObj)
        return newObj
    }

    handleAssignmentExpression(left: ExpressionContext, right: ExpressionContext) {
        const assignment = new AssignmentExpression()
        assignment.left = this.handleExpression(left)//.relate(assignment)
        assignment.right = this.handleExpression(right)//.relate(assignment)
        return assignment
    }

    handleBinaryExpression(operator: TerminalNode, left: ExpressionContext, right: ExpressionContext) {
        const binary = new BinaryExpression()
        binary.operator = operator.getText()
        binary.left = this.handleExpression(left)//.relate(binary)
        binary.right = this.handleExpression(right)//.relate(binary)
        return binary
    }

    handleUnaryExpression(operator: TerminalNode, argument: ExpressionContext, prefix: boolean = true) {
        const unary = new UnaryExpression()
        unary.operator = operator.getText()
        unary.argument = this.handleExpression(argument)//.relate(unary)
        unary.prefix = prefix
        return unary
    }

    handleIdentifier(tree: TerminalNode) {
        return Identifier.build(tree.getText()).loc(this.location(tree))
    }

    handleTerminal(tree: TerminalNode) {
        if (tree.symbol.type === ScriptGrammarLexer.ID)
            return Identifier.build(tree.getText()).loc(this.location(tree))
            // return {...this.location(tree), type: "Identifier", name: tree.getText()}
        if (tree.symbol.type === ScriptGrammarLexer.NUMBER)
            return Literal.build(parseFloat(tree.getText())).loc(this.location(tree))
        if (tree.symbol.type === ScriptGrammarLexer.HEX)
            return Literal.build(parseInt(tree.getText(), 16)).loc(this.location(tree))
        if (tree.symbol.type === ScriptGrammarLexer.OCT)
            return Literal.build(parseInt(tree.getText(), 8)).loc(this.location(tree))
        if (tree.symbol.type === ScriptGrammarLexer.BIN)
            return Literal.build(parseInt(tree.getText(), 2)).loc(this.location(tree))
        if (tree.symbol.type === ScriptGrammarLexer.STRING)
            return Literal.build(tree.getText()).loc(this.location(tree))
        if (tree.getText() === 'true')
            return Literal.build(true).loc(this.location(tree))
        if (tree.getText() === 'false')
            return Literal.build(false).loc(this.location(tree))
        return null
    }

    handleParseTree(tree: ParseTree, onBefore, onAfter) {
        if (!tree) return
        if (onBefore(tree)) return
        if (tree instanceof ParserRuleContext) {
            for (let i = 0; i < tree.children.length; i++) {
                const child = tree.children[i]
                this.handleParseTree(child, onBefore, onAfter)
            }
        }
        onAfter(tree)
    }

    private indexOfTerminals(children: Array<ParseTree>, term: number): number[] {
        const r: Array<number> = []
        for (let i = 0; i < children.length; i++) {
            const child = children[i]
            if (child instanceof TerminalNode && child.symbol.type === term)
                r.push(i)
        }
        return r
    }

    private findTerminals(children: Array<ParseTree>, term: number): TerminalNode[] {
        const r: Array<TerminalNode> = []
        for (let i = 0; i < children.length; i++) {
            const child = children[i]
            if (child instanceof TerminalNode && child.symbol.type === term)
                r.push(child)
        }
        return r
    }

    private findFirstParserRule(children: Array<ParseTree>, rule: number) {
        for (let i = 0; i < children.length; i++) {
            const child = children[i] as any
            if (child.ruleIndex && child.ruleIndex === rule)
                return child
        }
        return null
    }

    private findLastParserRule(children: Array<ParseTree>, rule: number) {
        for (let i = children.length - 1; i > -1; i--) {
            const child = children[i] as any
            if (child.ruleIndex && child.ruleIndex === rule)
                return child
        }
        return null
    }

    private unfoldMembers(tree: MembersContext): Array<Declaration> {
        if (tree === null) return []
        if (tree.children.length === 1) return [this.handleMember(tree.children[0] as MemberContext)]
        let r: Array<Declaration> = []
        for (const child of tree.children) {
            r = r.concat(this.unfoldMembers(child as MembersContext))
        }
        return r
    }

    private unfoldParams(tree: ParamsContext): Array<Identifier> {
        if (tree.children.length === 1)
            return [this.handleIdentifier(tree.children[0] as TerminalNode)]
        return [
            ...this.unfoldParams(tree.children[0] as ParamsContext),
            ...this.unfoldParams(tree.children[2] as ParamsContext)
        ]
    }

    private unfoldAccessExpression(tree: AccessExpressionContext): Array<Expression> {
        const first = tree.children[0]
        if (first instanceof TerminalNode) {
            if (first.getText() === '.') {
                return [this.handleMemberExpression(null, tree.children[1] as TerminalNode)]
            } else if (first.getText() === '[') {
                return [this.handleDynamicMemberExpression(null, tree.children[1] as ExpressionContext)]
            } else if (first.getText() === '(') {
                return [this.handleCallExpression(null,
                    tree.children.length === 3 ? (tree.children[1] as ArgumentsContext) : null)]
            }
            return []
        }
        return [
            ...this.unfoldAccessExpression(tree.children[0] as AccessExpressionContext),
            ...this.unfoldAccessExpression(tree.children[1] as AccessExpressionContext)
        ]
    }

    private unfoldArguments(tree: ArgumentsContext): Array<Expression> {
        if (tree === null) return []
        if (tree.children.length === 1) return [this.handleExpression(tree.children[0] as ExpressionContext)]
        return [
            ...this.unfoldArguments(tree.children[0] as ArgumentsContext),
            ...this.unfoldArguments(tree.children[2] as ArgumentsContext)
        ]
    }

    private unfoldStatements(tree: StatementsContext): Array<Statement> {
        const first = tree.children[0]
        if (!(first instanceof StatementsContext)) {
            if (first instanceof IfStatementContext)
                return [this.handleIfStatement(first)]
            else if (first instanceof ForStatementContext)
                return [this.handleForStatement(first)]
            else if (first instanceof WhileStatementContext)
                return [this.handleWhileStatement(first)]
            else if (first instanceof ReturnStatementContext)
                return [this.handleReturnStatement(first)]
            else if (first instanceof ContinueStatementContext)
                return [this.handleContinueStatement(first)]
            else if (first instanceof BreakStatementContext)
                return [this.handleBreakStatement(first)]
            else if (first instanceof BlockStatementContext)
                return [this.handleBlockStatement(first)]
            else if (first instanceof ExpressionContext)
                return [this.handleExpression(first)]
            return []
        }
        return [...this.unfoldStatements(first), ...this.unfoldStatements(tree.children[1] as StatementsContext)]
    }

    private unfoldMultiIfStatement(tree: MultiIfStatementContext): Array<IfStatement> {
        const first = tree.children[0]
        if (!(first instanceof MultiIfStatementContext)) {
            const r = new IfStatement().loc(this.location(tree))
            r.test = this.handleExpression(tree.children[2] as ExpressionContext)
            r.consequent = this.handleBlockStatement(tree.children[4] as BlockStatementContext)
            r.alternate = null
            return [r]
        }
        return [
            ...this.unfoldMultiIfStatement(first),
            ...this.unfoldMultiIfStatement(tree.children[2] as MultiIfStatementContext)
        ]
    }

    private location(tree: ParseTree) {
        if (tree instanceof TerminalNode) return {start: tree.symbol.start, end: tree.symbol.stop}
        else if (tree instanceof ParserRuleContext) return {start: tree.start.start, end: tree.stop.stop}
        else return {}
    }
}


