import {ASTBuilder} from "./ast.ts";
import {Interpreter} from "./interpreter.ts";

const input = "class Utility {\n" +
    "    counter = 0;\n" +
    "    def add(a, b) {\n" +
    "        return a + b;\n" +
    "    }\n" +
    "}\n" +
    "def main(argc, argv) {\n" +
    "    a = 12 + 2 * 3;\n" +
    "    println(a);\n" +
    "    return 0;\n" +
    "}"
const builder = new ASTBuilder()
console.info(input)
builder.compile(input)
const interpreter = new Interpreter()
console.info(builder.psi())
interpreter.loadProgram(builder.psi())
// console.info("context :", interpreter.context())
console.info(interpreter.toString())
interpreter.invoke('main', 0, [])
// console.info(JSON.stringify(builder.psi().dumps()))
// console.info("AST :", JSON.stringify(builder.toJSONString()))