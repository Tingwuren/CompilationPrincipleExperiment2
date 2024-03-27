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

## 编译LL1分析程序
all: LL1.c hashtable.c lex.c stack.c
	gcc $(CFLAGS) $^ -o LL1$(EXE_EXT)

## 运行LL1分析程序
run:
	$(RUN)LL1$(EXE_EXT)

clean:
	$(RM) LL1$(EXE_EXT) output.txt