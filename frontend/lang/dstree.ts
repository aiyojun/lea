import {uuid} from "./functools.ts";

export class TreeNode<T> {
    private _uuid       : string;
    private _value      : T;
    private _parent     : TreeNode<T> = null;
    private _children   : TreeNode<T>[] = [];
    constructor() {
        this._uuid = uuid()
    }
    setUuid(id: string) {
        this._uuid = id
        return this
    }
    uuid() {
        return this._uuid
    }
    relate(p: TreeNode<T>) {
        this._parent = p
        this._parent._children.push(this)
    }
    setParent(p: TreeNode<T>) {
        this._parent = p
    }
    getParent() {
        return this._parent
    }
    getChildren() {
        return this._children
    }
    addChild(c: TreeNode<T>) {
        this._children.push(c)
        return this
    }
    hasChild() {
        return this._children.length !== 0
    }
    setValue(v: T) {
        this._value = v
        return this
    }
    getValue() {
        return this._value
    }
    static build() {
        return new TreeNode()
    }
}

export class DSTree<T> {
    private _root   : TreeNode<T>   = null;
    private _stack  : TreeNode<T>[] = [];
    root() {
        return this._root
    }
    traverse(node: TreeNode<T>, fx: (node: TreeNode<T>) => boolean, fy: (node: TreeNode<T>) => void = node => {}) {
        if (fx(node)) return
        if (node.hasChild()) {
            for (const child of node.getChildren()) {
                this.traverse(child, fx, fy)
            }
        }
        fy(node)
    }
    find(uuid: string) {
        let target: TreeNode<T> = null
        this.traverse(this._root, (node) => {
            if (node.uuid() === uuid) {
                target = node
                return true
            }
            return false
        })
        return target
    }
    addNode(node: TreeNode<T>, parent_uuid: string | null = null) {
        let success = false
        if (parent_uuid === null) {
            if (this._root === null) {
                this._root = node
                success = true
            }
        } else {
            const p = this.find(parent_uuid)
            if (p !== null) {
                node.relate(p)
                success = true
            }
        }
        return success
    }
    push(node: TreeNode<T>) {
        if (this._stack.length === 0)
            this._root = node
        this._stack.push(node)
        return this
    }
    reduce(n: number) {
        const arr = this._stack.splice(this._stack.length - n)
        const p = this._stack[this._stack.length - 1]
        arr.forEach(x => x.relate(p))
        return this
    }
    printNode(node: TreeNode<T> = null, depth: number = 0) {
        if (node === null) {
            if (this._root !== null) {
                this.printNode(this._root)
            }
            return
        }
        const prefix = new Array(depth).fill('·').join('')
        console.info(`${depth} ${prefix}${node.getValue()['type'] + " " + (node.getValue()['target'] || "")}`)
        if (!node.hasChild()) return
        for (const child of node.getChildren()) {
            this.printNode(child, depth + 1)
        }
    }
}
