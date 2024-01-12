# 语法分析实验方法三实现
## 功能说明：
1. 构造识别该文法所有活前缀的DFA
2. 构造该文法的LR(1)分析表
3. 实现算法4.3，构造LR分析程序
## 运行说明：
1. 运行环境：win10+mingw+vscode+cmake+powershell
2. 运行方法：在method3目录下打开powershell，执行`make all`生成可执行文件LL1.exe，执行`make run`执行语法分析程序，执行`make clean`清理可执行文件LL1.exe和输出文件output.txt。
3. 输入文件：从method3目录下读取input.txt文件中的算数表达式。
4. 输出文件：将语法分析过程中产生的产生式输出到mothod3目录下的ouput.txt文件。
5. 终端输出：执行过程中中终端输出语法分析程序各个阶段的详细情况。