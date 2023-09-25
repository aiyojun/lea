ASM        =as
LEA        =../lea

all: run

check_build:
	@if [ ! -d $(build_dir) ]; then mkdir -p $(build_dir); fi

syntax: check_build
	@$(LEA) ./syntax.lea $(build_dir)/main.lea.asm

assemble: check_build
	@$(LEA) ./main.lea $(build_dir)/main.lea.asm >/dev/null

compile: assemble
	$(ASM) -o $(build_dir)/main.lea.o $(build_dir)/main.lea.asm
	$(CXX) -o main.lea.run $(build_dir)/main.lea.o -lc -no-pie

run: compile
	@echo "executing [main.lea.run]:"
	@./main.lea.run

clean:
	@rm -rf $(build_dir)/*