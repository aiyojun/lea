import {ASTBuilder} from "./ast.ts";
import {VirtualMachine} from "./vm.ts";
import {FunctionDeclaration} from "./psi.ts";
import {Interpreter} from "./interpreter.ts";




const input = `
def add(a, b) {return a + b;}
def main(argc, argv) {
    a = 10 + 3 * 2 - -add(1, 2);
    if (a > 10) {
        a = a - 10;
    }
    // while (a < 10) {
    //     a = a + 2;
    // }
    println(a);
    println("Hello World!");
    println(r"Hello
World!");
    return 0;
}

`
const builder = new ASTBuilder()
// console.info(input)
builder.compile(input)
const interpreter = new Interpreter()
interpreter.load(builder.psi())
// console.info(interpreter.vm())
interpreter.run()
// console.info(builder.psi())
// const vm = new VirtualMachine()
// vm.build(builder.psi().body[0] as FunctionDeclaration)
// console.info(vm.bytecode())
// const executor = new FunctionExecutor()
// executor.build(builder.psi().body[0] as FunctionDeclaration)
// console.info(executor)
// interpreter.loadProgram(builder.psi())
// console.info("context :", interpreter.context())
// console.info(interpreter.toString())
// interpreter.invoke('main', 0, [])

// console.info(JSON.stringify(builder.psi().dumps()))
// console.info("AST :", JSON.stringify(builder.toJSONString()))