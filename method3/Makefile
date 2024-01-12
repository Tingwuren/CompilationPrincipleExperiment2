## 编译LR分析程序
all: LR.c DFA.c lex.c stack.c
	gcc $(CFLAGS) $^ -o LR.exe

## 运行LL1分析程序
run:
	.\LR.exe

clean:
	del *.exe output.txt