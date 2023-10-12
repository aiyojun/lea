import {
    AssignmentExpression,
    BinaryExpression,
    CallExpression, DynamicMemberExpression,
    Expression, FunctionDeclaration, Identifier,
    Literal, MemberExpression,
    PsiElement,
    ReturnStatement,
    UnaryExpression
} from "./psi.ts";
import {
    extractString,
    isBoolean,
    isEvalLeaf,
    isFlatNumber,
    isIdentifier,
    isNull,
    isNumber,
    isString
} from "./psiutils.ts";
import {handle} from "./hdl.ts";
import {BuiltinFunction, ScopeProvider, Pt} from "./interpreter.ts";
import {VirtualMachine} from "./vm.ts";

export class Evaluator {
    constructor(private readonly callstack: ScopeProvider) {

    }

    evaluate(expr: Expression): Literal {
        // console.info(`[LANG] eval ${expr.toString()}`)
        const stack: any[] = []
        PsiElement.walk(expr,
            (el: PsiElement) => {
                if (el instanceof CallExpression) {
                    stack.push(this.evalCallExpression(el, el.arguments))
                    return true
                }
                if (el instanceof ReturnStatement) {
                    if (el.argument !== null) {
                        stack.push(this.evaluate(el.argument))
                    } else {
                        stack.push(Literal.build(null))
                    }
                    return true
                }
                if (isEvalLeaf(el)) stack.push(el)
                return false
            },
            (el: PsiElement) => {
                if (el instanceof BinaryExpression) {
                    const [l, r] = stack.splice(stack.length - 2, 2)
                    stack.push(this.evalBinaryExpression(el, l, r))
                    return
                }
                if (el instanceof UnaryExpression) {
                    stack.push(this.evalUnaryExpression(el, stack.pop()))
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
                    stack.push(this.evalAssignmentExpression(l, r))
                    return
                }
            }
        )
        const _r = stack.pop()
        if (_r instanceof Identifier) {
            return Literal.build(this.callstack.exchange(_r))
        } else if (_r instanceof Literal) {
            return _r
        } else {
            return null
        }
    }

    private evalAssignmentExpression(left: Identifier, right): Literal {
        const callstack = this.callstack
        const r = this.evaluate(right)
        callstack.record(left.name, r?.value)
        return r
    }

    private evalCallExpression(expr: CallExpression, args: Expression[]): Literal {
        const callee = expr.callee
        if (!isIdentifier(callee))
            this.reportException(`${callee.dumps()} is not callable!`)
        const functionName = (callee as Identifier).name
        const callstack = this.callstack
        const refs = callstack.ref(functionName)
        if (refs === null)
            throw new Error(`error: no such function ${functionName}`)
        const rArgs = args.map(arg => this.evaluate(arg))
        const func = refs.get(functionName)
        // console.info(`[LANG] ${functionName} ( ${rArgs.map(arg => `${arg.value}`).join(', ')} )`)
        if (func instanceof FunctionDeclaration) {
            const fnDecl = refs.get(functionName)
            callstack.push(Pt.call(fnDecl))
            fnDecl.params.forEach((param, i) => callstack.record(param.name, rArgs[i]))
            const vm = new VirtualMachine(this)
            vm.build(func)
            // console.info(vm.bytecode())
            const _r = vm?.jit()
            // console.info(`[LANG] call ${callee.toString()} : ${_r?.toString()}`)
            return _r
            // this.evalBlockStatement(fnDecl.body)
            // return Literal.build((callstack.pop() as CallPt).ret)
        } else if (func instanceof BuiltinFunction) {
            return Literal.build(func.impl(...rArgs.map(arg => arg.value)))
        }
    }

    private evalUnaryExpression(expr: UnaryExpression, e: Literal | Identifier): Literal {
        const op = expr.operator
        const ev = e instanceof Identifier ? Literal.build(this.callstack.exchange(e)) : e
        return handle([
            {match: () => (isFlatNumber(ev) || isNull(ev)) && op === '!', apply: () => Literal.build(! ev.value)},
            {match: () => isFlatNumber(ev) && op === '~', apply: () => Literal.build(~ ev.value)},
            {match: () => isFlatNumber(ev) && op === '+', apply: () => Literal.build(ev.value)},
            {match: () => isFlatNumber(ev) && op === '-', apply: () => Literal.build(- ev.value)},
            {match: () => true, apply: () => {throw new Error(`unknown unary expression, operation : ${op}, element : ${JSON.stringify(ev?.dumps())}`)}},
        ])
    }

    private evalBinaryExpression(expr: BinaryExpression, left: Literal | Identifier, right: Literal | Identifier): Literal {
        const op = expr.operator
        const lv = left  instanceof Identifier ? Literal.build(this.callstack.exchange(left))  : left
        const rv = right instanceof Identifier ? Literal.build(this.callstack.exchange(right)) : right
        return handle([
            {match: () => isNumber(lv) && isNumber(rv) && op === '+', apply: () => Literal.build(lv.value + rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '-', apply: () => Literal.build(lv.value - rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '*', apply: () => Literal.build(lv.value * rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '/', apply: () => Literal.build(lv.value / rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '%', apply: () => Literal.build(lv.value % rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '^', apply: () => Literal.build(lv.value ^ rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '|', apply: () => Literal.build(lv.value | rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '&', apply: () => Literal.build(lv.value & rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '>', apply: () => Literal.build(lv.value > rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '>=', apply: () => Literal.build(lv.value >= rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '<', apply: () => Literal.build(lv.value < rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '<=', apply: () => Literal.build(lv.value <= rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '==', apply: () => Literal.build(lv.value === rv.value)},
            {match: () => isNumber(lv) && isNumber(rv) && op === '!=', apply: () => Literal.build(lv.value !== rv.value)},
            {match: () => isBoolean(lv) && isBoolean(rv) && op === '>', apply: () => Literal.build(lv.value > rv.value)},
            {match: () => isBoolean(lv) && isBoolean(rv) && op === '>=', apply: () => Literal.build(lv.value >= rv.value)},
            {match: () => isBoolean(lv) && isBoolean(rv) && op === '<', apply: () => Literal.build(lv.value < rv.value)},
            {match: () => isBoolean(lv) && isBoolean(rv) && op === '<=', apply: () => Literal.build(lv.value <= rv.value)},
            {match: () => isBoolean(lv) && isBoolean(rv) && op === '==', apply: () => Literal.build(lv.value === rv.value)},
            {match: () => isBoolean(lv) && isBoolean(rv) && op === '!=', apply: () => Literal.build(lv.value !== rv.value)},
            {match: () => isString(lv) && isString(rv) && op === '>', apply: () => Literal.build(lv.value > rv.value)},
            {match: () => isString(lv) && isString(rv) && op === '>=', apply: () => Literal.build(lv.value >= rv.value)},
            {match: () => isString(lv) && isString(rv) && op === '<', apply: () => Literal.build(lv.value < rv.value)},
            {match: () => isString(lv) && isString(rv) && op === '<=', apply: () => Literal.build(lv.value <= rv.value)},
            {match: () => isString(lv) && isString(rv) && op === '==', apply: () => Literal.build(lv.value === rv.value)},
            {match: () => isString(lv) && isString(rv) && op === '!=', apply: () => Literal.build(lv.value !== rv.value)},
            {match: () => isNull(lv) && isNull(rv) && op === '==', apply: () => Literal.build(lv.value === rv.value)},
            {match: () => isNull(lv) && isNull(rv) && op === '!=', apply: () => Literal.build(lv.value !== rv.value)},
            {match: () => isString(lv) && isNumber(rv) && op === '+', apply: () => Literal.build(extractString(lv.value) + `${rv.value}`)},
            {match: () => isString(lv) && isString(rv) && op === '+', apply: () => Literal.build(extractString(lv.value) + extractString(rv.value))},
            {match: () => isString(lv) && isBoolean(rv) && op === '+', apply: () => Literal.build(extractString(lv.value) + `${rv.value ? 'true' : 'false'}`)},
            {match: () => isString(lv) && isNull(rv) && op === '+', apply: () => Literal.build(extractString(lv.value) + `${rv.value}`)},
            {match: () => true, apply: () => {throw new Error(`unknown binary expression, operation : ${op}, left : ${rv}, right : ${rv}`)}},
        ])
    }

    // private handleMemberExpression(object: any, property: Identifier): any {
    //     return null
    // }
    //
    // private handleDynamicMemberExpression(object: any, property: Expression): any {
    //     return null
    // }

    // private handleException(expr: Expression) {
    //     this.reportException(`${expr.textRange().line}:${expr.textRange().start}: error: evaluate failed, ${JSON.stringify(expr.dumps())}`)
    // }

    private reportException(msg: string) {
        console.error(`program:${msg}`)
        throw new Error
    }
}