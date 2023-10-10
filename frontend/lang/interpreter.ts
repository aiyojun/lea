import {
    AssignmentExpression,
    BinaryExpression,
    CallExpression,
    ClassDeclaration,
    Declaration,
    DynamicMemberExpression,
    Expression,
    FunctionDeclaration,
    Identifier,
    Literal,
    MemberExpression,
    Program,
    PsiElement,
    UnaryExpression,
    VariableDeclaration
} from "./psi.ts";
import {extractString, isBoolean, isEvalLeaf, isIdentifier, isFlatNumber, isString} from "./psiutils.ts";

// export type CallableFunction = Function // (...args) => any

// export class ObjectManager {
//
// }

export class BuiltinFunction {
    constructor(readonly name: string, readonly impl: Function) {
    }
}

// export class BuiltinProvider {
//     private _builtinFunctions: Map<string, CallableFunction> = new Map
//
//     containsFunction(name: string) { return this._builtinFunctions.has(name) }
//
//     invoke(functionName: string, ...args) { return this._builtinFunctions.get(functionName)(...args) }
// }

export class Scope {
    declaration: Declaration = null;
    identifiers: Map<string, any> = new Map;
    constructor(decl: Declaration) {
        this.declaration = decl
    }
}

export class GlobalScopeDeclaration extends Declaration {
    static self = new GlobalScopeDeclaration()

    private constructor() {
        super()
    }
}

export class RuntimeContext {
    private _chain: Array<Scope> = []

    constructor() {
        this._chain.push(new Scope(GlobalScopeDeclaration.self))
    }

    record(id: string, entity: any) {
        const _refs = this.refScope(id)
        _refs !== null ? _refs.set(id, entity) : this._chain[this._chain.length - 1].identifiers.set(id, entity)
    }

    exchange(id: Identifier) {
        const refs = this.refScope(id.name)
        if (refs === null) {
            // console.info(this.interpreter.context())
            throw new Error(`no such identifier : ${id.name}`)
        }
        return refs.get(id.name)
    }

    refScope(id: string) {
        let index = this._chain.length - 1
        while (index > -1) {
            if (this._chain[index].identifiers.has(id))
                return this._chain[index].identifiers
            index--
        }
        return null
    }

    pushNewScope(decl: FunctionDeclaration | ClassDeclaration) {
        this._chain.push(new Scope(decl))
        return this
    }

    popScope() {
        this._chain.pop()
        return this
    }
}

// export class LFunction {
//     private _declaration: FunctionDeclaration = null
//
//     setPrototype(decl: FunctionDeclaration) {
//         this._declaration = decl
//         return this
//     }
//
//     invoke(...args) {
//
//     }
// }

export class Evaluator {
    constructor(private readonly interpreter: Interpreter) {
    }

    private exchange(id: Identifier) {
        const refs = this.interpreter.context().refScope(id.name)
        if (refs === null) {
            // console.info(this.interpreter.context())
            throw new Error(`no such identifier : ${id.name}`)
        }
        return refs.get(id.name)
    }

    evaluate(expr: Expression): any {
        // console.info(`evaluate : ${JSON.stringify(expr.dumps())}`)
        const stack: any[] = []
        PsiElement.walk(expr,
            (el: PsiElement) => {
                if (el instanceof CallExpression) {
                    stack.push(this.handleCallExpression(el.callee, el.arguments))
                    return true
                }
                if (isEvalLeaf(el)) stack.push(el)
                return false
            },
            (el: PsiElement) => {
                if (el instanceof BinaryExpression) {
                    const [l, r] = stack.splice(stack.length - 2, 2)
                    stack.push(this.handleBinaryExpression(el.operator, l, r))
                    return
                }
                if (el instanceof UnaryExpression) {
                    stack.push(this.handleUnaryExpression(el.operator, stack.pop()))
                    return
                }
                if (el instanceof MemberExpression) {
                    stack.splice(stack.length - 2)
                    stack.push(null)
                    return
                }
                if (el instanceof DynamicMemberExpression) {
                    stack.splice(stack.length - 2)
                    stack.push(null)
                    return
                }
                if (el instanceof AssignmentExpression) {
                    const [l, r] = stack.splice(stack.length - 2)
                    if (!isIdentifier(l))
                        this.reportException(`${el.textRange().line}:${el.textRange().start}: error: identifier should be provided!`);
                    stack.push(this.handleAssignmentExpression(l, r))
                    return
                }
            }
        )
        const _r = stack.pop()
        if (_r instanceof Identifier) {
            return this.exchange(_r)
        } else if (_r instanceof Literal) {
            return _r.value
        } else {
            return
        }
    }

    private handleAssignmentExpression(left: Identifier, right): any {
        const context = this.interpreter.context()
        context.record(left.name, this.evaluate(right))
    }

    private handleUnaryExpression(op: string, e: Literal | Identifier, prefix: boolean = true): any {

    }

    private handleCallExpression(callee: any, args: Expression[]): any {
        if (!isIdentifier(callee))
            this.reportException(`${callee.dumps()} is not callable!`)
        return this.interpreter.invoke(callee.name, ...args.map(arg => this.evaluate(arg)))
    }

    private handleMemberExpression(object: any, property: Identifier): any {
        return null
    }

    private handleDynamicMemberExpression(object: any, property: Expression): any {
        return null
    }


    private handleBinaryExpression(op: string, left: Literal | Identifier, right: Literal | Identifier): any {
        let lv = left  instanceof Identifier ? Literal.build(this.interpreter.context().exchange(left))  : left
        let rv = right instanceof Identifier ? Literal.build(this.interpreter.context().exchange(right)) : right
        const options = [
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '+', _handle: () => Literal.build((left as Literal).value + (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '-', _handle: () => Literal.build((left as Literal).value - (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '*', _handle: () => Literal.build((left as Literal).value * (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '/', _handle: () => Literal.build((left as Literal).value / (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '%', _handle: () => Literal.build((left as Literal).value % (right as Literal).value)},
            {_match: () => isString(left) && isString(right) && op === '+', _handle: () => Literal.build(extractString((left as Literal).value) + extractString((right as Literal).value))},
            {_match: () => isString(left) && isFlatNumber(right) && op === '+', _handle: () => Literal.build(extractString((left as Literal).value) + `${(right as Literal).value}`)},
            {_match: () => isString(left) && isBoolean(right) && op === '+', _handle: () => Literal.build(extractString((left as Literal).value) + `${(right as Literal).value ? 'true' : 'false'}`)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '|', _handle: () => Literal.build((left as Literal).value | (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '&', _handle: () => Literal.build((left as Literal).value & (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '>', _handle: () => Literal.build((left as Literal).value > (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '>=', _handle: () => Literal.build((left as Literal).value >= (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '<', _handle: () => Literal.build((left as Literal).value < (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '<=', _handle: () => Literal.build((left as Literal).value <= (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '==', _handle: () => Literal.build((left as Literal).value === (right as Literal).value)},
            {_match: () => isFlatNumber(left) && isFlatNumber(right) && op === '!=', _handle: () => Literal.build((left as Literal).value !== (right as Literal).value)},
            {_match: () => isString(left) && isString(right) && op === '==', _handle: () => Literal.build((left as Literal).value === (right as Literal).value)},
            {_match: () => isString(left) && isString(right) && op === '!=', _handle: () => Literal.build((left as Literal).value !== (right as Literal).value)},
            // {_match: () => isIdentifier(left), _handle: () => Literal.build(this.handleIdentifierFirst(op, left as Identifier, right))},
            // {_match: () => isIdentifier(right), _handle: () => Literal.build(this.handleIdentifierSecond(expr))},
            {_match: () => true, _handle: () => { throw new Error('unknown expression') }},
        ]
        for (let i = 0; i < options.length; i++) {
            const option = options[i]
            if (option._match())
                return option._handle()
        }
        return null
    }

    private handleIdentifierFirst(op: string, left: Identifier, right: Literal | Identifier): any {

    }

    private handleIdentifierSecond(expr: BinaryExpression): any {

    }

    private handleException(expr: Expression) {
        this.reportException(`${expr.textRange().line}:${expr.textRange().start}: error: evaluate failed, ${JSON.stringify(expr.dumps())}`)
    }

    private reportException(msg: string) {
        console.error(`program:${msg}`)
        throw new Error
    }
}

export class Interpreter {
    private _program: Program = null

    private _classes: Map<string, ClassDeclaration> = new Map

    // private _functions: Map<string, FunctionDeclaration> = new Map
    //
    // private _variables: Map<string, VariableDeclaration> = new Map

    // private _builtin: BuiltinProvider = new BuiltinProvider()

    private _context: RuntimeContext = new RuntimeContext()

    private _evaluator: Evaluator = new Evaluator(this)

    context() { return this._context }

    loadProgram(p: Program) {
        this._program = p
        this._program.body.forEach(decl => {
            if (decl instanceof ClassDeclaration) {
                this._classes.set(decl.id.name, decl)
                return
            }
            if (decl instanceof VariableDeclaration) {
                this._context.record(decl.id.name, decl)
                // this._variables.set(decl.id.name, decl)
                return
            }
            if (decl instanceof FunctionDeclaration) {
                this._context.record(decl.id.name, decl)
                // this._functions.set(decl.id.name, decl)
                return
            }
        })
        const println = new BuiltinFunction("println", (...args) => {
            let stream = ''
            for (let i = 0; i < args.length; i++) {
                stream += `${args[i]}`
            }
            console.info("%c[MOON]", "color: #88cc88", `${stream}`)
        })
        this._context.record(println.name, println)
    }

    invoke(functionName: string, ...args) {
        const context = this._context
        const refs = context.refScope(functionName)
        if (refs === null)
            throw new Error(`error: no such function ${functionName}`)
        const func = refs.get(functionName)
        if (func instanceof FunctionDeclaration) {
            console.info(`[LANG] ${functionName} ( ${args.map(arg => `${arg}`).join(', ')} )`)
            const fnDecl = refs.get(functionName)
            context.pushNewScope(fnDecl)
            fnDecl.params.forEach((param, i) => context.record(param.name, args[i]))
            fnDecl.body.body.forEach(stmt => this._evaluator.evaluate(stmt))
            return
        } else if (func instanceof BuiltinFunction) {
            console.info(`[LANG] ${functionName} ( ${args.map(arg => `${arg}`).join(', ')} )`)
            return func.impl(...args)
        }
    }

    newObject() {

    }

    toString() {
        let buffer = ""
        buffer += "Type System:\n"
        this._classes.forEach((cls, identifier) => {
            buffer += `  class ${identifier} {\n`
            cls.variables.forEach(variable => {
                buffer += `    ${variable.id.name};\n`
            })
            cls.methods.forEach(method => {
                buffer += `    ${method.id.name} ( ${method.params.map(p => p.name).join(", ")} );\n`
            })
            buffer += `  }`
        })
        return buffer
    }
}




