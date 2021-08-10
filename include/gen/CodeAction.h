//
// Created by Mr.Jun on 2021/8/9.
//

#ifndef LEA_CODEACTION_H
#define LEA_CODEACTION_H

#include "../STL.h"

/**
 * Prepared for code execution
 */
class CodeAction {
public:
    CodeAction();
    void addMain();
    void show();
    void M_Def();
    void M_Ret(int r);
    void D_Def(const std::string& label, const std::string& s);
    void F_Call(const std::vector<std::string>& args, const std::string& label);
    static CodeAction codeAction;
private:
    std::vector<std::string> nasm_seq;
    std::vector<std::string> section_data;
    std::vector<std::string> section_text;
};


#endif //LEA_CODEACTION_H
