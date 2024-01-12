# 语法分析实验方法二实现
## 功能说明：
1. 实现文法的读入
2. 实现文法的左递归消除
3. 实现文法的FIRST集合构造
4. 实现文法的FOLLOW集合构造
5. 实现LL1预测分析程序
## 运行说明：
1. 运行环境：win10+mingw+vscode+cmake+powershell
2. 运行方法：在method2目录下打开powershell，执行`make all`生成可执行文件LL1.exe，执行`make run`执行语法分析程序，执行`make clean`清理可执行文件LL1.exe和输出文件output.txt。
3. 输入文件：从method2目录下读取input.txt文件中的算数表达式。
4. 输出文件：将语法分析过程中产生的产生式输出到method2目录下ouput.txt文件。
5. 终端输出：执行过程中中终端输出语法分析程序各个阶段的详细情况。