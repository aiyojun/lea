// PSI: program structure interface

export class TextRange {
    start: number;
    end: number;
}

export class PsiElement {
    private _parent: PsiElement = null

    private _children: PsiElement[] = []

    private _textRange: TextRange = new TextRange()

    parent(): PsiElement { return this._parent }

    children(): PsiElement[] { return this._children }

    textRange(): TextRange { return this._textRange }

    relate(p: PsiElement) {
        this._parent = p
        if (p._children.indexOf(p) === -1)
            p._children.push(this)
        return this
    }

    loc(obj: Record<string, any>) {
        this._textRange.start = obj.start
        this._textRange.end = obj.end
        return this
    }

    dumps(): Record<string, any> { return {start: this._textRange.start, end: this._textRange.end} }

    static walk(el: PsiElement, onBefore: (e: PsiElement) => boolean, onAfter: (e: PsiElement) => void = null) {
        if (!el || onBefore(el)) return
        for (const child of el.children()) {
            PsiElement.walk(child, onBefore, onAfter)
        }
        if (onAfter) onAfter(el)
    }
}

export class Program extends PsiElement {
    body: Declaration[] = [];
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "Program", body: this.body.map(s => s?.dumps())};
    }
}

export class Declaration extends PsiElement {
}

export class Statement extends PsiElement {
}

export class Expression extends PsiElement {
}

export class ClassDeclaration extends Declaration {
    private _id: Identifier;
    variables: VariableDeclaration[] = [];
    methods: FunctionDeclaration[] = [];
    get id(): Identifier { return this._id }
    set id(id: Identifier) { this._id = id; this._id?.relate(this) }
    dumps(): Record<string, any> {
        return {
            ...super.dumps(), type: "ClassDeclaration", id: this._id?.dumps(),
            variables: this.variables.map(v => v?.dumps()),
            methods: this.methods.map(m => m?.dumps())};
    }
}

export class FunctionDeclaration extends Declaration {
    private _id: Identifier;
    private _body: BlockStatement;
    params: Identifier[] = [];
    get id(): Identifier { return this._id }
    set id(id: Identifier) { this._id = id; this._id?.relate(this) }
    get body(): BlockStatement { return this._body }
    set body(e: BlockStatement) { this._body = e; this._body?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "FunctionDeclaration", id: this._id?.dumps(), params: this.params.map(p => p?.dumps()), body: this._body?.dumps()};
    }
}

export class VariableDeclaration extends Declaration {
    private _id: Identifier;
    private _init: Expression;
    get id(): Identifier { return this._id }
    set id(id: Identifier) { this._id = id; this._id?.relate(this) }
    get init(): Expression { return this._init }
    set init(e: Expression) { this._init = e; this._init?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "VariableDeclaration", id: this._id?.dumps(), init: this._init?.dumps()};
    }
}

export class BlockStatement extends Statement {
    body: Statement[] = [];
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "BlockStatement", body: this.body.map(s => s?.dumps())};
    }
}

export class IfStatement extends Statement {
    private _test: Expression;
    private _consequent: BlockStatement;
    private _alternate: IfStatement | BlockStatement;
    get test(): Expression { return this._test }
    set test(e: Expression) { this._test = e; this._test?.relate(this) }
    get consequent(): BlockStatement { return this._consequent }
    set consequent(e: BlockStatement) { this._consequent = e; this._consequent?.relate(this) }
    get alternate(): IfStatement | BlockStatement { return this._alternate }
    set alternate(e: IfStatement | BlockStatement) { this._alternate = e; this._alternate?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "IfStatement", test: this._test?.dumps(), consequent: this._consequent?.dumps(), alternate: this._alternate?.dumps()};
    }
}

export class LoopStatement extends Statement {
}

export class ForStatement extends LoopStatement {
    private _init: Expression;
    private _test: Expression;
    private _update: Expression;
    private _body: BlockStatement;
    get init(): Expression { return this._init }
    set init(e: Expression) { this._init = e; this._init?.relate(this) }
    get test(): Expression { return this._test }
    set test(e: Expression) { this._test = e; this._test?.relate(this) }
    get update(): Expression { return this._update }
    set update(e: Expression) { this._update = e; this._update?.relate(this) }
    get body(): BlockStatement { return this._body }
    set body(e: BlockStatement) { this._body = e; this._body?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "ForStatement", init: this._init?.dumps(), test: this._test?.dumps(), update: this._update?.dumps(), body: this._body?.dumps()};
    }
}

export class ForeachStatement extends LoopStatement {
    private _left: Expression;
    private _right: Expression;
    private _body: BlockStatement;
    get left(): Expression { return this._left }
    set left(e: Expression) { this._left = e; this._left?.relate(this) }
    get right(): Expression { return this._right }
    set right(e: Expression) { this._right = e; this._right?.relate(this) }
    get body(): BlockStatement { return this._body }
    set body(e: BlockStatement) { this._body = e; this._body?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "ForeachStatement", left: this._left?.dumps(), right: this._right?.dumps(), body: this._body?.dumps()};
    }
}

export class WhileStatement extends LoopStatement {
    private _test: Expression;
    private _body: BlockStatement;
    get test(): Expression { return this._test }
    set test(e: Expression) { this._test = e; this._test?.relate(this) }
    get body(): BlockStatement { return this._body }
    set body(e: BlockStatement) { this._body = e; this._body?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "WhileStatement", test: this._test?.dumps(), body: this._body?.dumps()};
    }
}

export class ReturnStatement extends Statement {
    private _argument: Expression;
    get argument(): Expression { return this._argument }
    set argument(e: Expression) { this._argument = e; this._argument?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "ReturnStatement", argument: this._argument?.dumps()};
    }
}

export class ContinueStatement extends Statement {
}

export class BreakStatement extends Statement {
}

export class BinaryExpression extends Expression {
    operator: string;
    private _left: Expression;
    get left(): Expression { return this._left }
    set left(e: Expression) { this._left = e; this._left?.relate(this) }
    private _right: Expression;
    get right(): Expression { return this._right }
    set right(e: Expression) { this._right = e; this._right?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "BinaryExpression", operator: this.operator, left: this._left?.dumps(), right: this._right?.dumps()};
    }
}

export class UnaryExpression extends Expression {
    prefix: boolean;
    operator: string;
    private _argument: Expression;
    get argument(): Expression { return this._argument }
    set argument(e: Expression) { this._argument = e; this._argument?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "UnaryExpression", operator: this.operator, prefix: this.prefix, argument: this._argument?.dumps()};
    }
}

export class NewExpression extends Expression {
    arguments: Expression[] = [];
    private _callee: Identifier;
    get callee(): Identifier { return this._callee }
    set callee(id: Identifier) { this._callee = id; this._callee?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "NewExpression", callee: this._callee?.dumps(), arguments: this.arguments.map(arg => arg?.dumps())};
    }
}

export class CallExpression extends Expression {
    arguments: Expression[] = [];
    private _callee: Expression;
    get callee(): Expression { return this._callee }
    set callee(e: Expression) { this._callee = e; this._callee?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "CallExpression", callee: this._callee?.dumps(), arguments: this.arguments.map(arg => arg?.dumps())};
    }
}

export class MemberExpression extends Expression {
    protected _object_: Expression;
    protected _property: Expression;
    get object_(): Expression { return this._object_ }
    set object_(e: Expression) { this._object_ = e; this._object_?.relate(this) }
    get property(): Expression { return this._property }
    set property(e: Expression) { this._property = e; this._property?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "MemberExpression", "object": this._object_?.dumps(), property: this._property?.dumps()};
    }
}

export class DynamicMemberExpression extends MemberExpression {
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "DynamicMemberExpression", "object": this._object_?.dumps(), property: this._property?.dumps()};
    }
}

export class AssignmentExpression extends Expression {
    private _left: Expression;
    private _right: Expression;
    get left(): Expression { return this._left }
    set left(e: Expression) { this._left = e; this._left?.relate(this) }
    get right(): Expression { return this._right }
    set right(e: Expression) { this._right = e; this._right?.relate(this) }
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "AssignmentExpression", operator: "=", left: this._left?.dumps(), right: this._right?.dumps()};
    }
}

export class Identifier extends Expression {
    name: string;
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "Identifier", name: this.name};
    }
    static build(name: string): Identifier {
        const r = new Identifier()
        r.name = name
        return r
    }
}

export class Literal extends Expression {
    value: any;
    dumps(): Record<string, any> {
        return {...super.dumps(), type: "Literal", value: this.value};
    }
    static build(v: any): Literal {
        const r = new Literal()
        r.value = v
        return r
    }
}
