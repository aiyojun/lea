#include "syntax.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>

struct VI_ATOM {
	int deep = 0;
	int type = -1;
	int args = 0;
	char name[512];
	/* record execute info */
};

struct EX_ATOM {
	char value[512];
	int type = -1;
};

class EX_DEEP_ATOM {
public:
	int deep = 0;
	std::vector<EX_ATOM> stack_ex;
};

/** place for variable definition */
int lealine = 1;
int vi_deep = 0;
std::map<int, VI_ATOM> vis_m;
std::map<int, EX_DEEP_ATOM> stack_ex_m;
bool ex_is_open = false;
// std::vector<EX_ATOM> stack_ex;

std::vector<std::string> asm_data_s;
std::vector<std::string> asm_text_s;
#define A(x) asm_text_s.emplace_back(x)

void printf_empty(const char *__restrict __format, ...) {}

void vi_register(char* name) {
	// if (vi_deep == -1) 
	vi_deep++;
	// printf("[vi] ---- begin { %d %s\n", vi_deep, name);
	VI_ATOM vi_a;
	vi_a.deep = vi_deep;
	strcpy(vi_a.name, name);
	vis_m[vi_deep] = vi_a;
}
void vi_args() {
	vis_m[vi_deep].args++;
}
void vi_end_var() {
	// printf("[vi] variable : %s\n", vis_m[vi_deep].name);
	vis_m[vi_deep].type = 5;

	vi_deep--;
	ex_push_vi(vis_m[vi_deep+1]);

	// if (vi_deep == -1) printf("[vi] ---- }\n");
}
void vi_end_inv() {
	// printf(">>ncadn\n");
	// printf("[vi] function : %s, args : %d\n", vis_m[vi_deep].name, vis_m[vi_deep].args);
	vis_m[vi_deep].type = 6;

	// printf("xxx deep: %d ;  \n", vi_deep);
	ex_invoke(vis_m[vi_deep].args, vis_m[vi_deep].name);
	vi_deep--;
	ex_push_vi(vis_m[vi_deep+1]);

	// if (vi_deep == -1) printf("[vi] ---- }\n");
}

// 0->int 1->double 2->bool 3->char 4->string 5->variable 6->function invoke 7->asm label
void ex_open() {if (!ex_is_open) ex_is_open = true;}
void ex_close() {ex_is_open = false;ex_show();}
void ex_push(EX_ATOM ea) {
	int vi_deep_p = vi_deep == -1 ? 0 : vi_deep;
	if (stack_ex_m.end() == stack_ex_m.find(vi_deep_p)) {
		EX_DEEP_ATOM eda;
		eda.deep = vi_deep_p;
		eda.stack_ex.emplace_back(ea);
	}
	stack_ex_m[vi_deep_p].stack_ex.emplace_back(ea);
}
void ex_push_v(EX_ATOM ea) {
	int vi_deep_p = vi_deep == -1 ? 0 : vi_deep;
	if (stack_ex_m.end() == stack_ex_m.find(vi_deep_p)) {
		EX_DEEP_ATOM eda;
		eda.deep = vi_deep_p;
		eda.stack_ex.emplace_back(ea);
	}
	stack_ex_m[vi_deep_p].stack_ex.emplace_back(ea);
}
void ex_push_i(int i) {
	// printf(">>>> %d\n", vi_deep);
	EX_ATOM ex_a;
	sprintf(ex_a.value, "%d", i);
	ex_a.type = 0;
	ex_push(ex_a);
	// stack_ex.emplace_back(ex_a);
	ex_show();
}
void ex_push_d(double d) {
	EX_ATOM ex_a;
	sprintf(ex_a.value, "%f", d);
	ex_a.type = 1;
	ex_push(ex_a);
	// stack_ex.emplace_back(ex_a);
	ex_show();
	// printf("push\n");
}
void ex_push_s(char* s) {
	EX_ATOM ex_a;
	strcpy(ex_a.value, s);
	ex_a.type = 1;
	ex_push(ex_a);
	ex_show();
}
void ex_push_c(char c) {
	EX_ATOM ex_a;
	sprintf(ex_a.value, "%c", c);
	ex_a.type = 1;
	ex_push(ex_a);
	ex_show();
}
void ex_push_vi(const VI_ATOM& vi) {
	EX_ATOM ex_a;
	sprintf(ex_a.value, "%s", vi.name);
	ex_a.type = vi.type;
	ex_push_v(ex_a);
	// stack_ex.emplace_back(ex_a);
	ex_show();
	// printf("push\n");
}
void ex_invoke(int n, char *fun) {
	// pop args from stack_ex
	// printf(">> %d\n", (vi_deep <= -1 ? 0 : vi_deep));
	std::vector<EX_ATOM>& stack_ex = stack_ex_m[vi_deep <= -1 ? 0 : vi_deep].stack_ex;
	for (int i = 0; i < n; i++) {
		stack_ex.pop_back();
	}
	EX_ATOM ea;
	strcpy(ea.value, fun);
	ea.type = 7;
	stack_ex.emplace_back();
}
void ex_calculate(int n, char *op) {
	std::vector<EX_ATOM>& stack_ex = stack_ex_m[vi_deep <= -1 ? 0 : vi_deep].stack_ex;
	if (n == 2) 
		printf("calc: %s %s %s ", stack_ex[stack_ex.size() - 2].value, op, stack_ex[stack_ex.size() - 1].value);
	else
		printf("calc: %s %s ", op, stack_ex[stack_ex.size() - 1].value);
	// ----------------
	if (n == 2) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		if (n0.type >= 5) {
			// printf("tick out : %s - %s\n", n0.value, n1.value);
			stack_ex.pop_back();
			stack_ex.pop_back();
			EX_ATOM n3; strcpy(n3.value, n0.value);
			n3.type = 7;
			stack_ex.emplace_back(n3);
			return;
		} else if (n1.type >= 5) {
			// printf("tick out : %s - %s\n", n0.value, n1.value);
			stack_ex.pop_back();
			stack_ex.pop_back();
			EX_ATOM n3; strcpy(n3.value, n1.value);
			n3.type = 7;
			stack_ex.emplace_back(n3);
			return;
		}
	}
	// ----------------
	if (strcmp(op, "*") == 0) {
		printf("-*\n");
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 1;
			double n3_d = atof(n0.value) * atof(n1.value);
			sprintf(n3.value, "%f", n3_d);
		} else {
			n3.type = 0;
			int n3_i = atoi(n0.value) * atoi(n1.value);
			printf("i*i : %d\n", n3_i);
			sprintf(n3.value, "%d", n3_i);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "/") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1) {
			n3.type = 1;
			double n3_d = atof(n0.value) / atof(n1.value);
			sprintf(n3.value, "%f", n3_d);
		} else {
			n3.type = 0;
			int n3_i = atoi(n0.value) / atof(n1.value);
			sprintf(n3.value, "%d", n3_i);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "+") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 1;
			double n3_d = atof(n0.value) + atof(n1.value);
			sprintf(n3.value, "%f", n3_d);
		} else {
			n3.type = 0;
			int n3_i = atoi(n0.value) + atoi(n1.value);
			sprintf(n3.value, "%d", n3_i);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "-") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 1;
			double n3_d = atof(n0.value) - atof(n1.value);
			sprintf(n3.value, "%f", n3_d);
		} else {
			n3.type = 0;
			int n3_i = atoi(n0.value) - atoi(n1.value);
			sprintf(n3.value, "%d", n3_i);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, ">") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 0;
			int n3_b;
			if (atof(n0.value) - atof(n1.value) > 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		} else {
			n3.type = 0;
			int n3_b;
			if (atoi(n0.value) - atoi(n1.value) > 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "<") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 0;
			int n3_b;
			if (atof(n0.value) - atof(n1.value) < 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		} else {
			n3.type = 0;
			int n3_b;
			if (atoi(n0.value) - atoi(n1.value) < 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, ">=") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 0;
			int n3_b;
			if (atof(n0.value) - atof(n1.value) >= 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		} else {
			n3.type = 0;
			int n3_b;
			if (atoi(n0.value) - atoi(n1.value) >= 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "<=") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 0;
			int n3_b;
			if (atof(n0.value) - atof(n1.value) <= 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		} else {
			n3.type = 0;
			int n3_b;
			if (atoi(n0.value) - atoi(n1.value) <= 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "==") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 0;
			int n3_b;
			if (atof(n0.value) - atof(n1.value) == 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		} else {
			n3.type = 0;
			int n3_b;
			if (atoi(n0.value) - atoi(n1.value) == 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "!=") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		if (n0.type == 1 || n1.type == 1) {
			n3.type = 0;
			int n3_b;
			if (atof(n0.value) - atof(n1.value) != 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		} else {
			n3.type = 0;
			int n3_b;
			if (atoi(n0.value) - atoi(n1.value) != 0) n3_b = 1; else n3_b = 0;
			sprintf(n3.value, "%d", n3_b);
		}
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "&&") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		n3.type = 0;
		int n3_b;
		if (atoi(n0.value) == 1 && atoi(n1.value) == 1) n3_b = 1; else n3_b = 0;
		sprintf(n3.value, "%d", n3_b);
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "||") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 2];
		EX_ATOM n1 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		n3.type = 0;
		int n3_b;
		if (atoi(n0.value) == 1 || atoi(n1.value) == 1) n3_b = 1; else n3_b = 0;
		sprintf(n3.value, "%d", n3_b);
		stack_ex.pop_back();
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else if (strcmp(op, "!") == 0) {
		EX_ATOM n0 = stack_ex[stack_ex.size() - 1];
		EX_ATOM n3;
		n3.type = 0;
		int n3_b;
		if (atoi(n0.value) == 1) n3_b = 0; else n3_b = 1;
		sprintf(n3.value, "%d", n3_b);
		stack_ex.pop_back();
		stack_ex.emplace_back(n3);
	} else {
		printf("unknown op %s ???\n", op);
		return;
	}
	printf(" = %s\n", stack_ex[stack_ex.size() - 1].value);
}
void ex_show() {
	// printf("---begin %d\n", vi_deep);
	// printf("all: ");
	for (const auto& stack : stack_ex_m) {
		printf("stack#%d#%d: ", stack.first, stack.second.stack_ex.size());
		for (const auto& item : stack.second.stack_ex) {
			printf("%s | ", item.value);
		}
		printf("\n");
	}
	// for (const auto& ex_a : stack_ex) {
	// 	printf("%s | ", ex_a.value);
	// }
	// printf("\n");
	printf("---\n");
}

/** data generation */
void g_add_i(int i, int j) {
	A("mov -"+std::to_string(i)+"(%rbp),%rax");
	A("mov -"+std::to_string(j)+"(%rbp),%rbx");
	A("add %rbx,%rax");
}

void g_invoke(const std::string& fun, std::string args[], int size) {
    if (size > 5) {
        printf("Beyond args limitation!\n");
        exit(1);
    }
	std::string reg_seq[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
	for (int i = 0; i < size; i++) {
		A("mov $" + args[i] + ",%" + reg_seq[i]);
	}
	A("call "+fun);
}