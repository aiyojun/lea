import {TreeNode} from "./dstree.ts";


// PSI: program structure interface

export class Program {
    body: Declaration[];
}
export class Declaration {}
export class ClassDeclaration extends Declaration {
    id: string;
    variables: VariableDeclaration[];
    methods: FunctionDeclaration[];
}
export class FunctionDeclaration extends Declaration {
    id: string;
    params: string[];
    body: BlockStatement;
}
export class VariableDeclaration extends Declaration {
    id: string;
    init: Expression;
}
export class Statement {}
export class BlockStatement extends Statement {
    body: Statement[];
}
export class IfStatement extends Statement {
    test: Expression;
    consequent: BlockStatement;
    alternate: IfStatement | BlockStatement;
}
export class ForStatement extends Statement {
    init: Expression;
    test: Expression;
    update: Expression;
    body: BlockStatement;
}
export class ForeachStatement extends Statement {
    left: Expression;
    right: Expression;
    body: BlockStatement;
}
export class WhileStatement extends Statement {
    test: Expression;
    body: BlockStatement;
}
export class ReturnStatement extends Statement {
    argument: Expression;
}
export class ContinueStatement extends Statement {}
export class BreakStatement extends Statement {}
export class Expression {}
export class BinaryExpression extends Expression {
    operator: string;
    left: Expression;
    right: Expression;
}
export class UnaryExpression extends Expression {
    operator: string;
    argument: Expression;
    prefix: boolean;
}
export class NewExpression extends Expression {
    callee: string;
    arguments: Expression[];
}
export class CallExpression extends Expression {
    callee: Expression;
    arguments: Expression[];
}
export class MemberExpression extends Expression {
    object_: Expression;
    property: string;
}
export class DynamicMemberExpression extends Expression {
    object_: Expression;
    property: Expression;
}
export class AssignmentExpression extends Expression {
    left: Expression;
    right: Expression;
}



export class Interpreter {

    deserialize(s: Record<string, any>): Program {
        return new Program()
    }

    handleBinaryExpression(node: TreeNode<Record<string, any>>) {

    }

}








