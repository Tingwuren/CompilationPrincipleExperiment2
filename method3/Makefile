# 判断操作系统类型
ifeq ($(OS),Windows_NT)
    EXE_EXT = .exe
    RM = del
    RUN = .\\
else
    EXE_EXT =
    RM = rm -f
    RUN = ./
endif

## 编译LR分析程序
all: LR.c DFA.c lex.c stack.c
	gcc $(CFLAGS) $^ -o LR$(EXE_EXT)

## 运行LR分析程序
run:
	$(RUN)LR$(EXE_EXT)

clean:
	$(RM) LR$(EXE_EXT) output.txt