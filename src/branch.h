#ifndef __branch_h__
#define __branch_h__

// branch
void branch_clear();
std::string branch_new();
void do_compare();
namespace lea_if {
    void allocate_label();
};
#endif//__branch_h__