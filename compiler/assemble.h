#ifndef __assemble_h__
#define __assemble_h__

#include <vector>
#include <string>
#include <map>
#include <string.h>

typedef cstring=const std::string&;

#define G(x) g_text.emplace_back(x)
#define D(x) g_data.emplace_back(x)
#define M(x) g_main.emplace_back(x)
#define GA(x, n) g_text.emplace_back(a_align({x}, n))
#define DA(x, n) g_data.emplace_back(a_align({x}, n))
#define MA(x, n) g_main.emplace_back(a_align({x}, n))

std::string g_align(std::string& seq[], int n) {
	char buf[512] = {0};
	sprintf(buf, "    ");
	int index = 4;
	for (int i = 0; i < n; i++) {
		sprintf(buf + index, "%10s", seq[i]);
		index += 10;
	}
	buf[index + 1] = '\0';

	return std::move(std::string(buf));
}

class Assembler {
public:
	void def_glb_var(cstring name, cstring type, cstring value) {
		// g_data, g_text
		GA(".globl", name, 2);
		D(name+":");
		DA("."+type, value, 2);
	}
	void def_glb_fun(cstring name) {
		// g_text
/*		.text
		.globl	func
		.type	func, @function
	func:*/
		GA(".globl", name, 2);
		G(name+":");
	}
	void def_var(cstring name, cstring type, cstring value) {
		// g_text
		
	}
	void inv_fun() {
		// g_text
	}

// private:
	int stack_p = 0;
	int stack_bp = 0;
	int stack_sp = 0;
	std::string scope;
	std::vector<std::string> g_text;
	std::vector<std::string> g_data;
	std::vector<std::string> g_main;
}

#endif//__assemble_h__