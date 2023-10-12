import {
    CallExpression,
    ClassDeclaration,
    FunctionDeclaration,
    Identifier, Literal,
    Program,
    PsiElement,
    VariableDeclaration
} from "./psi.ts";
import {Evaluator} from "./eval.ts";
import {VirtualMachine} from "./vm.ts";
// Scope Field
// Builtin Provider BuiltinFunction
// Environment Context
// System Type ClassLoader
// GarbageCollector ObjectManager
// GIL GIR
// Call Stack
// record register

export class BuiltinFunction {
    constructor(readonly name: string, readonly impl: Function) {

    }
}

// callstack point
export class StkPt {
    element: PsiElement
    identifiers: Map<string, any> = new Map

    constructor(el: PsiElement) {
        this.element = el
    }
}

export class GlobalPt extends StkPt {
    static self: GlobalPt = new GlobalPt(null)
}

export class CallPt extends StkPt {
    ret: any;
}

export class LoopPt extends StkPt {
}

export class BlockPt extends StkPt {
}

export class Pt {
    static call(el: PsiElement) {
        return new CallPt(el)
    }

    static loop(el: PsiElement) {
        return new LoopPt(el)
    }

    static block(el: PsiElement) {
        return new BlockPt(el)
    }
}

export class ScopeProvider {
    // save identifier and its value
    private _callstack: Array<StkPt> = []

    constructor() {
        this._callstack.push(GlobalPt.self)
    }

    record(id: string, entity: any) {
        const _refs = this.ref(id)
        _refs !== null ? _refs.set(id, entity) : this._callstack[this._callstack.length - 1].identifiers.set(id, entity)
    }

    exchange(id: Identifier) {
        const refs = this.ref(id.name)
        if (refs === null) {
            // console.info(this.interpreter.callstack())
            throw new Error(`no such identifier : ${id.name}`)
        }
        return refs.get(id.name)
    }

    func(): CallPt {
        for (let i = this._callstack.length - 1; i > -1; i--) {
            const sco = this._callstack[i]
            if (sco instanceof CallPt)
                return sco
        }
        return null
    }

    ref(id: string) {
        let index = this._callstack.length - 1
        while (index > -1) {
            if (this._callstack[index].identifiers.has(id))
                return this._callstack[index].identifiers
            index--
        }
        return null
    }

    push(pt: StkPt) {
        this._callstack.push(pt)
        return this
    }

    pop() {
        return this._callstack.pop()
    }
}

export class Interpreter {
    private _program: Program = null

    private _classes: Map<string, ClassDeclaration> = new Map

    // private _functions: Map<string, FunctionDeclaration> = new Map
    //
    // private _variables: Map<string, VariableDeclaration> = new Map
    //
    // private _builtin: BuiltinProvider = new BuiltinProvider()

    private _scopeProvider: ScopeProvider = new ScopeProvider()

    private readonly _evaluator: Evaluator

    private _vm: VirtualMachine

    constructor() {
        this._evaluator = new Evaluator(this._scopeProvider)
        this._vm = new VirtualMachine(this._evaluator)
    }

    callstack() { return this._scopeProvider }

    load(p: Program) {
        this._program = p
        this._program.body.forEach(decl => {
            if (decl instanceof ClassDeclaration) {
                this._classes.set(decl.id.name, decl)
                return
            }
            if (decl instanceof VariableDeclaration) {
                this._scopeProvider.record(decl.id.name, decl)
                // this._variables.set(decl.id.name, decl)
                return
            }
            if (decl instanceof FunctionDeclaration) {
                this._scopeProvider.record(decl.id.name, decl)
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
        this._scopeProvider.record(println.name, println)
    }

    run() {
        const _main = new CallExpression()
        _main.callee = Identifier.build("main")
        _main.arguments = [Literal.build(0), Literal.build(null)]
        return this._evaluator.evaluate(_main)
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




