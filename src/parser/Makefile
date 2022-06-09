TARGET  =rv
LEX     =flex
YACC    =bison
CXX     =gcc

all: build_dir lex yacc
	@echo "[3/3] Compiling lex.yy.c $(TARGET).tab.c"
	@$(CXX) -std=c++11 -o $(TARGET) build/$(TARGET).yacc.cc build/$(TARGET).lex.cc main.cpp core.cpp -lstdc++ -lc

build_dir:
	@if [ ! -d build ]; then mkdir build; fi

lex:
	@echo "[1/3] Compiling lex file"
	@$(LEX) -+ -o build/$(TARGET).lex.cc $(TARGET).l

yacc:
	@echo "[2/3] Compiling yacc file"
	@$(YACC) -L C++ -Wcounterexamples -d -o build/$(TARGET).yacc.cc concise.y -v
#	@$(YACC) -L C++ -Wcounterexamples -d -o build/$(TARGET).yacc.cc $(TARGET).y -v
#	@$(YACC) -L C++ -Wcounterexamples -d -o build/$(TARGET).yacc.cc structure.y -v

clean:
	@rm -rf build $(TARGET)

.PHONY: clean
