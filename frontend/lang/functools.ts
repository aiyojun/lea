// import * as CryptoJS from "crypto-js";
//
// export function hash(o) {
//     return CryptoJS.MD5(JSON.stringify(o)).toString()
// }

export function uuid() {
    const t = new Date().getTime().toString(16)
    return new Array(32).fill(0).map((_, i) =>
        i % 2 === 0 && i / 2 < t.length ? t[i / 2] : Math.floor(Math.random() * 16).toString(16)).reverse().join('')
}

export const clone = obj => JSON.parse(JSON.stringify(obj))

export function isBasicType(a) {
    return typeof a === 'number'
        || typeof a === 'string'
        || typeof a === 'boolean'
        || a === null
}

export function isObject(a) {
    return typeof a === 'object' && !Array.isArray(a)
}

export function exists(o: any, k?: string) {
    if (k === undefined)
        return o !== undefined && o !== null
    return typeof o === 'object' && o !== null
        && !(o instanceof Array) && Object.keys(o).includes(k)
        && o[k] !== undefined && o[k] !== null
}

export function getDefault(data: any, key: string, defaultValue: any) {
    return exists(data, key) ? data[key] : defaultValue
}

export async function http_send(method, url, body, headers) {
    return {data: null}
}

export function CodeSpace(func_space: Record<string, any>, script: string) {
    const sandbox = {window: null, document: null, eval: null, ...func_space}
    const args = Array.from(Object.keys(sandbox))
    const rArgs = args.map(n => sandbox[n])
    return (new Function(...args, script))(...rArgs)
}

export const AsyncFunction = Object.getPrototypeOf(async function () {
}).constructor

export async function AsyncCodeSpace(func_space: Record<string, any>, script: string) {
    const sandbox = {document: null, eval: null, window: null, ...func_space}
    const args = Array.from(Object.keys(sandbox))
    const rArgs = args.map(n => sandbox[n])
    return await (new AsyncFunction(...args, script))(...rArgs)
}

export function execute(func_space: Record<string, any>, script: string) {
    return CodeSpace({...func_space}, script)
}

export async function async_execute(func_space: Record<string, any>, script: string) {
    return await AsyncCodeSpace({...func_space, dumpJson: (data: any) => JSON.stringify(data)}, script)
}