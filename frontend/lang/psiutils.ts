import {Identifier, Literal, PsiElement} from "./psi.ts";

export function isNumber(psi: PsiElement)
{ return psi instanceof Literal && typeof psi.value === 'number' }

export function isString(psi: PsiElement)
{ return psi instanceof Literal && typeof psi.value === 'string' }

export function extractString(text: string) {
    if (text[0] === '\'' && text[text.length - 1] === '\'') return text.substring(1, text.length - 1)
    else if (text[0] === '"' && text[text.length - 1] === '"') return text.substring(1, text.length - 1)
    else if (text.startsWith('r"') && text[text.length - 1] === '"') return text.substring(2, text.length - 1)
    else return ""
}

export function isBoolean(psi: PsiElement)
{ return psi instanceof Literal && typeof psi.value === 'boolean' }

export function isIdentifier(psi: PsiElement)
{ return psi instanceof Identifier }

export function isEvalLeaf(psi: PsiElement)
{ return psi instanceof Literal || psi instanceof Identifier }

