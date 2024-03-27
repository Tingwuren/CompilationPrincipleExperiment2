#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DFA.h"
#include "stack.h"
#include "LR.h"
#include "lex.h"

struct State state[16];
char s[100]; // 存储从输入文件中读入的字符串
char token[100]; // 存储词法分析的符号表
// DFA转换表
int go[NUM_STATES][NUM_INPUTS] = {
    //  +             -           *           /           (           )          num          $           E           T           F
    // STATE_0
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_4,    STATE_ERROR,STATE_5,    STATE_ERROR,STATE_1,    STATE_2,    STATE_3},
    // STATE_1
    {STATE_6,    STATE_7,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ACC,  STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_2
    {STATE_ERROR,STATE_ERROR,STATE_8,    STATE_9,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_3
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_4
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_4,    STATE_ERROR,STATE_5,    STATE_ERROR,STATE_10,   STATE_2,    STATE_3},
    // STATE_5
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_6
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_4,    STATE_ERROR,STATE_5,    STATE_ERROR,STATE_ERROR,STATE_11,   STATE_3},
    // STATE_7
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_4,    STATE_ERROR,STATE_5,    STATE_ERROR,STATE_ERROR,STATE_12,   STATE_3},
    // STATE_8
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_4,    STATE_ERROR,STATE_5,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_13},
    // STATE_9
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_4,    STATE_ERROR,STATE_5,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_14},
    // STATE_10
    {STATE_6,    STATE_7,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_15   ,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_11
    {STATE_ERROR,STATE_ERROR,STATE_8,    STATE_9,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_12
    {STATE_ERROR,STATE_ERROR,STATE_8,    STATE_9,    STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_13
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_14
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR},
    // STATE_15
    {STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR,STATE_ERROR}
};

int main() {
    // 构造识别该文法所有活前缀的DFA
    ConstructDFA(); 

    // 构造分析表
    ConstructTable();
    printf("\n");
    
    // 词法分析得到记号流
    lexical_analysis();
    printf("This is the token flow:\n");
    print_token();

    // 构造分析程序
    printf("This is the analysis process:\n");
    analysis_process();
    return 0;
}

void ConstructTable(){
    // 遍历所有状态
    for(int i = 0; i < NUM_STATES; i++){
        // 对于状态i的分析动作如下
        // printState(&state[i]);
        for(int j = 0; j <(state[i].numItems); j++) {
            struct Item item = getItem(&state[i], j);
            printItem(&state[i], j);
        }
    }
}

void analysis_process() {
    FILE *fp; // 定义一个文件指针
    fp = fopen("output.txt", "w"); // 打开一个输出文件，如果不存在则创建，如果存在则覆盖
    if (fp == NULL) { // 如果打开失败
        printf("无法打开文件\n"); // 输出错误信息
        return; // 返回非零值，表示程序异常退出
    }
    // 完成输入字符串和分析栈的初始化
    int size = 100; // 定义栈的最大容量为100
    Stack *status = init(size); // 初始化状态栈
    Stack *symbol = init(size); // 初始化符号栈
    push(status, '0');
    push(symbol, '-');

    int len = strlen(token); // 获取字符串token的长度
    // printf("len: %d\n", len);
    token[len] = '$'; // 在字符串token的末尾添加$符号
    token[len + 1] = '\0'; // 在字符串token的最后添加空字符，表示字符串的结束

    len = strlen(token);
    char* c = token;
    char S;
    top(status, &S);
    int acc = do_one_analysis(status, symbol, &c, fp);
    while (acc != 0) {
        // printf("analysis: %c, %c\n", e, c);
        acc = do_one_analysis(status, symbol, &c, fp); // 根据栈顶元素和当前分析字符完成一次分析
        // printf("acc: %d\n", acc);
        top(status, &S);
    }

    printf("ACC\n");
    fclose(fp); // 关闭文件
}

int do_one_analysis(Stack *status,  Stack *symbol, char **c, FILE *fp) {
    printf("Status ");
    print_status_stack(status);
    printf("Symbol ");
    print_stack(symbol);
    printf(" Token: ");
    printf("%s\n", *c);

    char S;
    char m;
    top(status, &S); // S 是栈顶状态，**c是ip指向的符号
    int num = S - '0';

    if(Action[num][hash_a(**c)][0] == 'S') {
        push(symbol, **c);
        if(Action[num][hash_a(**c)][2]!= '\0') {
            char c1 = Action[num][hash_a(**c)][1];
            char c2 = Action[num][hash_a(**c)][2];
            int num1 = c1 - '0';
            int num2 = c2 - '0';
            int new = num1 * 10 + num2;
            push(status, new+'0');
            *c = *c + 1;
            return 1;
        }
        push(status, Action[num][hash_a(**c)][1]);
        *c = *c + 1; 
        return 1;
    }
    else if(Action[num][hash_a(**c)][0]== 'R') {
        int num3 = Action[num][hash_a(**c)][1] - '0';
        char* right = get_right(num3);
        int len = strlen(right);
        for(int i=0; i<len; i++) {
            pop(status,&S);
            pop(symbol,&m);
        }
        
        char A = get_left(num3);
        push(symbol, A);
        top(status,&m);
        int num2 = m -'0';
        int new = Goto[num2][hash_A(A)];
        char new_state = new +'0';
        push(status, new_state);
        //printf("%d\n", new);
        printf("%c -> %s\n", A, right);
        fprintf(fp, "%c->%s\n", A, right);
        return 1;
    }
    else if(Action[num][hash_a(**c)] == "ACC")
        return 0;
}

int hash_a(char c) {
    switch(c){
        case '+':
        return 0;
        case '-':
        return 1;
        case '*':
        return 2;
        case '/':
        return 3;
        case '(':
        return 4;
        case ')':
        return 5;
        case 'n':
        return 6;
        case '$':
        return 7;
    }
}

int hash_A(char c){
    switch (c)
    {
    case 'E':
        return 0;
    case 'T':
        return 1;
    case 'F':
        return 2;
    }
}

char* get_right(int num) {
    switch(num) {
        case 0:
        return "E";
        case 1:
        return "E+T";
        case 2:
        return "E-T";
        case 3:
        return "T";
        case 4:
        return "T*F";
        case 5:
        return "T/F";
        case 6:
        return "F";
        case 7:
        return "(E)";
        case 8:
        return "n";
    }
}

char get_left(int num) {
    switch(num) {
        case 0:
        return 'S';
        case 1:
        return 'E';
        case 2:
        return 'E';
        case 3:
        return 'E';
        case 4:
        return 'T';
        case 5:
        return 'T';
        case 6:
        return 'T';
        case 7:
        return 'F';
        case 8:
        return 'F';
    }
}