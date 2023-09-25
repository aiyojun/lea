# FAQ

## 前端

- Right Value: 独立的右值系统
- Closure: 闭包赋值
- IF/FOR: 流程控制，区块划分，区块控制(continue,break,return)
- Type System: 支持复杂的类型系统，可供查询分析
- Scope: 构造域
- Symbol Table: 带域空间的符号记录表
- Middle Value Space: 为中间值分配空间(DAG)
- Register Allocator: 寄存器染色(DAG，偏后端)
- List/Map/Json: 更便捷的构造语法糖

### Tips

- Loop: 引入更简单的循环机制，考虑更高的并行度
- Type Match: 引入类型匹配
- 尾递归
- 尾调用
- Functor: 函数式，函数一等公民

## 后端

- Lazy Evaluation: 惰性求值
- GC: 面向对象，垃圾收集器
- Memory Allocator: 对象内存空间分配
- Isolated Assemble: 独立的线性码流

## 组件方式

完全分离，灵活组合，子类继承

