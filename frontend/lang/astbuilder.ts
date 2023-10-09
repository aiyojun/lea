import {
    CharStream,
    CommonTokenStream,
    ErrorListener,
    ParserRuleContext,
    ParseTree,
    TerminalNode, Token,
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
import {TreeNode} from "./dstree.ts";

export class ScriptGrammarErrorListener extends ErrorListener<Token> {
    syntaxError(recognizer: Recognizer<Token>, offendingSymbol: Token, line: number, column: number, msg: string, e: RecognitionException | undefined): void {
        throw new Error(`program:${line}:${column}: error: ${msg}`)
    }
}

export class ASTBuilder {
    private _ASTJson: Record<string, any> = null
    private _withLocation: boolean = true

    toJSONString() { return this._ASTJson }

    setLocation(b: boolean) { this._withLocation = b; return this }

    compile(input: string) {
        const chars = new CharStream(input);
        const lexer = new ScriptGrammarLexer(chars);
        const tokens = new CommonTokenStream(lexer);
        const parser = new ScriptGrammarParser(tokens);
        parser.removeErrorListeners()
        parser.addErrorListener(new ScriptGrammarErrorListener())
        try {
            const tree = parser.program();
            builder.handleProgram(tree)
        } catch (e) {
            console.error(e)
        }
    }

    handleProgram(program: ParseTree) {
        const AST: Record<string, any> = {...this.location(program), type: "Program", body: []}
        this.handleParseTree(program,
                tree => {
                    if (tree instanceof ClassDeclarationContext) {
                        const identifiers = this.findTerminals(tree.children, ScriptGrammarLexer.ID)
                        AST.body.push({
                            ...this.location(tree), type: "ClassDeclaration",
                            id: this.handleIdentifier(identifiers[0]),
                            members: this.unfoldMembers(
                                this.findFirstParserRule(tree.children, ScriptGrammarParser.RULE_members))
                        })
                        return true
                    }
                    if (tree instanceof VariableDeclarationContext) {
                        AST.body.push(this.handleVariableDeclaration(tree))
                        return true
                    }
                    if (tree instanceof FunctionDeclarationContext) {
                        AST.body.push(this.handleFunctionDeclaration(tree))
                        return true
                    }
                    return false
                },
                tree => {}
            )
        this._ASTJson = AST
    }

    handleMember(tree: MemberContext): Record<string, any> {
        if (tree.children[0] instanceof VariableDeclarationContext)
            return this.handleVariableDeclaration(tree.children[0])
        if (tree.children[0] instanceof FunctionDeclarationContext)
            return this.handleFunctionDeclaration(tree.children[0])
    }

    handleVariableDeclaration(tree: VariableDeclarationContext): Record<string, any> {
        return {...this.location(tree), type: "VariableDeclaration",
            id: this.handleIdentifier(tree.children[0] as TerminalNode),
            init: this.handleExpression(tree.children[2] as ExpressionContext)}
    }

    handleFunctionDeclaration(tree: FunctionDeclarationContext): Record<string, any> {
        const params = this.findFirstParserRule(tree.children, ScriptGrammarParser.RULE_params)
        return {...this.location(tree),
            type: "FunctionDeclaration",
            id: this.handleIdentifier(tree.children[1] as TerminalNode),
            params: params !== null ? this.unfoldParams(params) : [],
            body: this.handleBlockStatement(tree.children[tree.children.length - 1] as BlockStatementContext)
        }
    }

    handleStatements(tree: StatementsContext): Array<Record<string, any>> {
        return this.unfoldStatements(tree);
    }

    handleIfStatement(tree: IfStatementContext): Record<string, any> {
        const conditions =
            this.unfoldMultiIfStatement(tree.children[0] as MultiIfStatementContext)
        let index = 1
        let iter = conditions[0]
        while (index < conditions.length) {
            iter.alternate = conditions[index]
            iter = conditions[index]
            index++
        }
        const elseStatement = tree.children[1] as ElseStatementContext
        if (elseStatement.children.length > 0)
            conditions[conditions.length - 1].alternate =
                this.handleBlockStatement(elseStatement.children[1] as BlockStatementContext)
        return {...this.location(tree), ...conditions[0]}
    }

    handleForStatement(tree: ForStatementContext): Record<string, any> {
        const semi = this.indexOfTerminals(tree.children, ScriptGrammarLexer.SEMI)
        const isNumeric = semi.length > 0
        if (isNumeric) {
            return {
                ...this.location(tree),
                type  : "ForStatement",
                init  : tree.children[semi[0] - 1] instanceof ExpressionContext
                    ? this.handleExpression(tree.children[semi[0] - 1] as ExpressionContext) : null,
                test  : tree.children[semi[1] - 1] instanceof ExpressionContext
                    ? this.handleExpression(tree.children[semi[1] - 1] as ExpressionContext) : null,
                update: tree.children[semi[2] - 1] instanceof ExpressionContext
                    ? this.handleExpression(tree.children[semi[2] - 1] as ExpressionContext) : null,
                body  : this.handleBlockStatement(tree.children[tree.children.length - 1] as BlockStatementContext),
            }
        } else {
            return {
                ...this.location(tree),
                type  : "ForeachStatement",
                left  : this.handleExpression(tree.children[2] as ExpressionContext),
                right : this.handleExpression(tree.children[4] as ExpressionContext),
                body  : this.handleBlockStatement(tree.children[tree.children.length - 1] as BlockStatementContext),
            }
        }
    }

    handleWhileStatement(tree: WhileStatementContext): Record<string, any> {
        return {...this.location(tree), type: "WhileStatement",
            test: this.handleExpression(tree.children[2] as ExpressionContext),
            body: this.handleBlockStatement(tree.children[4] as BlockStatementContext)}
    }

    handleReturnStatement(tree: ReturnStatementContext): Record<string, any> {
        return {...this.location(tree), type: "ReturnStatement",
            argument: tree.children.length === 2 ? this.handleExpression(tree.children[1] as ExpressionContext) : null}
    }

    handleContinueStatement(tree: ContinueStatementContext): Record<string, any> {
        return {...this.location(tree), type: "ContinueStatement"}
    }

    handleBreakStatement(tree: BreakStatementContext): Record<string, any> {
        return {...this.location(tree), type: "BreakStatement"}
    }

    handleBlockStatement(tree: BlockStatementContext): Record<string, any> {
        return {...this.location(tree), type: "BlockStatement",
            body: tree.children.length === 3 ? this.handleStatements(tree.children[1] as StatementsContext) : []}
    }

    handleExpression(tree: ExpressionContext): Record<string, any> {
        if (tree.children[0] instanceof TerminalNode && tree.children[0].getText() === '(') {
            let obj: Record<string, any> = this.handleExpression(tree.children[1] as ExpressionContext)
            const last = tree.children[tree.children.length - 1] as any
            if (last.ruleIndex && last.ruleIndex === ScriptGrammarParser.RULE_accessExpression) {
                obj = this.handleAccessExpression(obj, last)
            }
            return {...this.location(tree), ...obj}
        }
        if (tree.children[0] instanceof TerminalNode && tree.children[0].getText() === 'new') {
            let obj: Record<string, any> = this.handleNewExpression(tree.children[1] as TerminalNode, [])
            const last = tree.children[tree.children.length - 1] as any
            if (last.ruleIndex && last.ruleIndex === ScriptGrammarParser.RULE_accessExpression) {
                obj = this.handleAccessExpression(obj, last)
            }
            return {...this.location(tree), ...obj}
        }
        if (tree.children[0] instanceof TerminalNode && tree.children[0].symbol.type === ScriptGrammarLexer.ID) {
            let obj: Record<string, any> = this.handleIdentifier(tree.children[0])
            const last = tree.children[tree.children.length - 1] as any
            if (last.ruleIndex && last.ruleIndex === ScriptGrammarParser.RULE_accessExpression) {
                obj = this.handleAccessExpression(obj, last)
            }
            return {...this.location(tree), ...obj}
        }
        if (tree.children.length === 1) { return this.handleTerminal(tree.children[0] as TerminalNode) }
        if (tree.children.length === 2
            && tree.children[0] instanceof TerminalNode
            && tree.children[1] instanceof ExpressionContext) {
            return {...this.location(tree), ...this.handleUnaryExpression(tree.children[0], tree.children[1])}
        }
        if (tree.children.length === 2
            && tree.children[0] instanceof ExpressionContext
            && tree.children[1] instanceof TerminalNode) {
            return {
                ...this.location(tree),
                ...this.handleUnaryExpression(tree.children[1], tree.children[0], false)
            }
        }
        if (tree.children.length === 3
            && tree.children[0] instanceof ExpressionContext
            && tree.children[1] instanceof TerminalNode
            && tree.children[2] instanceof ExpressionContext
        ) {
            return tree.children[1].getText() === '='
                ? {
                    ...this.location(tree),
                    ...this.handleAssignmentExpression(tree.children[0], tree.children[2])
                }
                : {
                    ...this.location(tree),
                    ...this.handleBinaryExpression(tree.children[1], tree.children[0], tree.children[2])
                }
        }
        return {}
    }

    handleAccessExpression(obj: Record<string, any>, tree: AccessExpressionContext) {
        const seq = this.unfoldAccessExpression(tree)
        let index = 0
        let iObj = obj
        while (index < seq.length) {
            if (Object.hasOwn(seq[index], "callee")) {
                seq[index].callee = iObj
            } else {
                seq[index].object = iObj
            }
            iObj = seq[index]
            index++
        }
        return iObj
    }

    handleMemberExpression(obj: Record<string, any>, id: TerminalNode) {
        return {type: "MemberExpression", object: obj, property: this.handleTerminal(id)}
    }

    handleDynamicMemberExpression(obj: Record<string, any>, expr: ExpressionContext) {
        return {type: "MemberExpression", object: obj, property: this.handleExpression(expr)}
    }

    handleCallExpression(obj: Record<string, any>, args: ArgumentsContext) {
        return {type: "CallExpression", callee: obj, arguments: this.unfoldArguments(args)}
    }

    handleNewExpression(callee: TerminalNode, _arguments: Array<ExpressionContext>) {
        return {type: "NewExpression", callee: this.handleIdentifier(callee), arguments: []}
    }

    handleAssignmentExpression(left: ExpressionContext, right: ExpressionContext) {
        return {type: "AssignmentExpression", operator: '=',
            left: this.handleExpression(left), right: this.handleExpression(right)}
    }

    handleBinaryExpression(operator: TerminalNode, left: ExpressionContext, right: ExpressionContext) {
        return {type: "BinaryExpression", operator: operator.getText(),
            left: this.handleExpression(left), right: this.handleExpression(right)}
    }

    handleUnaryExpression(operator: TerminalNode, argument: ExpressionContext, prefix: boolean = true) {
        return {type: "UnaryExpression", operator: operator.getText(), argument: this.handleExpression(argument)}
    }

    handleIdentifier(tree: TerminalNode): Record<string, any> {
        return {...this.location(tree), type: "Identifier", name: tree.getText()}
    }

    handleTerminal(tree: TerminalNode) {
        if (tree.symbol.type === ScriptGrammarLexer.ID)
            return {...this.location(tree), type: "Identifier", name: tree.getText()}
        if (tree.symbol.type === ScriptGrammarLexer.NUMBER)
            return {...this.location(tree), type: "Literal", value: parseFloat(tree.getText())}
        if (tree.symbol.type === ScriptGrammarLexer.HEX)
            return {...this.location(tree), type: "Literal", value: parseInt(tree.getText(), 16)}
        if (tree.symbol.type === ScriptGrammarLexer.OCT)
            return {...this.location(tree), type: "Literal", value: parseInt(tree.getText(), 8)}
        if (tree.symbol.type === ScriptGrammarLexer.BIN)
            return {...this.location(tree), type: "Literal", value: parseInt(tree.getText(), 2)}
        if (tree.symbol.type === ScriptGrammarLexer.STRING)
            return {...this.location(tree), type: "Literal", value: tree.getText()}
        if (tree.getText() === 'true')
            return {...this.location(tree), type: "Literal", value: true}
        if (tree.getText() === 'false')
            return {...this.location(tree), type: "Literal", value: false}
        return {}
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

    private unfoldMembers(tree: MembersContext): Array<Record<string, any>> {
        if (tree === null) return []
        if (tree.children.length === 1) return [this.handleMember(tree.children[0] as MemberContext)]
        else return tree.children.map(child => this.unfoldMembers(child as MembersContext))
    }

    private unfoldParams(tree: ParamsContext): Array<Record<string, any>> {
        if (tree.children.length === 1)
            return [this.handleIdentifier(tree.children[0] as TerminalNode)]
        return [
            ...this.unfoldParams(tree.children[0] as ParamsContext),
            ...this.unfoldParams(tree.children[2] as ParamsContext)
        ]
    }

    private unfoldAccessExpression(tree: AccessExpressionContext) {
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

    private unfoldArguments(tree: ArgumentsContext): Array<Record<string, any>> {
        if (tree === null) return []
        if (tree.children.length === 1) return [this.handleExpression(tree.children[0] as ExpressionContext)]
        return [
            ...this.unfoldArguments(tree.children[0] as ArgumentsContext),
            ...this.unfoldArguments(tree.children[2] as ArgumentsContext)
        ]
    }

    private unfoldStatements(tree: StatementsContext): Array<Record<string, any>> {
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

    private unfoldMultiIfStatement(tree: MultiIfStatementContext): Array<Record<string, any>> {
        const first = tree.children[0]
        if (!(first instanceof MultiIfStatementContext)) {
            return [{
                type: "IfStatement",
                test: this.handleExpression(tree.children[2] as ExpressionContext),
                consequent: this.handleBlockStatement(tree.children[4] as BlockStatementContext),
                alternate: null
            }]
        }
        return [
            ...this.unfoldMultiIfStatement(first),
            ...this.unfoldMultiIfStatement(tree.children[2] as MultiIfStatementContext)
        ]
    }

    private location(tree: ParseTree) {
        if (!this._withLocation) return {}
        if (tree instanceof TerminalNode) return {start: tree.symbol.start, end: tree.symbol.stop}
        else if (tree instanceof ParserRuleContext) return {start: tree.start.start, end: tree.stop.stop}
        else return {}
    }
}

const input = "def main(argc, argv) {\n" +
    "    (43 < 24) || (p0 <= pp0( p1, 12 + 32 + 43, \"haha\"  ));" +
    "    a = 12 + add(32, 12) * 43;\n" +
    "    if (a < 0) {\n" +
    "        a = 2 + a;\n" +
    "    } else if (a == 0) {\n" +
    "        print(a);\n" +
    "    } else {\n" +
    "        a = a - 10;\n" +
    "    }\n" +
    "    \twhile (1) {\n" +
    "      \n" +
    "    }" +
    "    return a + 5;\n" +
    "}"
const builder = new ASTBuilder()
builder.compile(input)
console.info("AST :", JSON.stringify(builder.toJSONString()))

