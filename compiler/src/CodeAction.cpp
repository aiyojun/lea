//
// Created by Mr.Jun on 2021/8/9.
//

#include "../include/gen/CodeAction.h"
#include "../include/gen/FileWriter.h"
#include <string.h>
#include <stdlib.h>

CodeAction CodeAction::codeAction;

CodeAction::CodeAction() {
    section_data.emplace_back(".section .data");
    section_text.emplace_back(".section .text");
}

void CodeAction::M_Def() {
    section_text.emplace_back(".global main");
    section_text.emplace_back("main:");
    section_text.emplace_back("  push %rbp");
    section_text.emplace_back("  mov  %rsp,%rbp");
}
void CodeAction::M_Ret(int r) {
    char as[50]; sprintf(as, "%x", r);
    section_text.emplace_back("  mov  $0x" + std::string(as) + ",%eax");
    section_text.emplace_back("  pop  %rbp");
    section_text.emplace_back("  ret");
}

void CodeAction::D_Def(const std::string& label, const std::string& s) {
    section_data.emplace_back("" + label + ":");
    section_data.emplace_back(".ascii " + s);
}

void CodeAction::F_Call(const std::vector<std::string>& args, const std::string& label) {
    if (args.size() > 5) {
        std::cout << "Beyond args limitation!" << std::endl;
        exit(1);
    }
    std::vector<std::string> reg_seq{"rdi", "rsi", "rdx", "rcx", "r8", "r9"}; // then push into stack
    for (int i = 0; i < args.size(); i++) {
    section_text.emplace_back("  mov  $" + args[i] + ",%" + reg_seq[i]);
    }
    section_text.emplace_back("  call " + label);
}

void CodeAction::addMain() {
//    nasm_seq.emplace_back(".section .data");
//    nasm_seq.emplace_back("string_format: .ascii \"hello: %d\n\"");
//    nasm_seq.emplace_back(".section .text");
//    nasm_seq.emplace_back(".globl main");
//    nasm_seq.emplace_back("main:");
//    nasm_seq.emplace_back("\tpush %rbp");
//    nasm_seq.emplace_back("\tmov  %rsp,%rbp");
//    nasm_seq.emplace_back("\tmov  %edi,-0x4(%rbp)");
//    nasm_seq.emplace_back("\tmov  $0x01,%rdi");
//    nasm_seq.emplace_back("\tmov  $0x02,%rsi");
//    nasm_seq.emplace_back("\tcall addv2");
//    nasm_seq.emplace_back("\tmov  $string_format,%rdi");
//    nasm_seq.emplace_back("\tmov  %rax,%rsi");
//    nasm_seq.emplace_back("\tcall printf");
//    nasm_seq.emplace_back("\tmov  $0x0,%eax");
//    nasm_seq.emplace_back("\tpop  %rbp");
//    nasm_seq.emplace_back("\tret");
}

void CodeAction::show() {
    FileWriter writer;
    writer.open("build/main.lea.asm");
    for (const auto& gas : section_data) {
        std::cout << gas << std::endl;
        writer.write(gas + "\n");
    }
    for (const auto& gas : section_text) {
        std::cout << gas << std::endl;
        writer.write(gas + "\n");
    }
//    for (const auto& gas : nasm_seq) {
//        std::cout << gas << std::endl;
//        writer.write(gas + "\n");
//    }
    writer.close();
}