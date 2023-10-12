import {Identifier, Literal, PsiElement} from "./psi.ts";

export function isNumber(psi: PsiElement)
{ return psi instanceof Literal && typeof psi.value === 'number' }

export function isFlatNumber(psi: PsiElement)
{ return psi instanceof Literal && (typeof psi.value === 'number' || typeof psi.value === 'boolean') }

export function isString(psi: PsiElement)
{ return psi instanceof Literal && typeof psi.value === 'string' }

export function extractString(text: string) {
    if (text[0] === '\'' && text[text.length - 1] === '\'') return text.substring(1, text.length - 1)
    else if (text[0] === '"' && text[text.length - 1] === '"') return text.substring(1, text.length - 1)
    else if (text.startsWith('r"') && text[text.length - 1] === '"') return text.substring(2, text.length - 1)
    else return ""
}

export function extractValue(psi: Literal) {
    if (isString(psi)) return extractString((psi as Literal).value)
    else return (psi as Literal)?.value
}

export function isBoolean(psi: PsiElement)
{ return psi instanceof Literal && typeof psi.value === 'boolean' }

export function isNull(psi: PsiElement)
{ return psi instanceof Literal && psi.value === null }

export function isIdentifier(psi: PsiElement)
{ return psi instanceof Identifier }

export function isEvalLeaf(psi: PsiElement)
{ return psi instanceof Literal || psi instanceof Identifier }
