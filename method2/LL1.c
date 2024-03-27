#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "LL1.h"
#include "hashtable.h"
#include "lex.h"

char s[100]; // 存储从输入文件中读入的字符串
char token[100]; // 存储词法分析的符号表
production* hash_table[BUCKET_SIZE]; // 哈希表是一个指向产生式的指针数组
production* M[52][10]; // LL1分析表
char FIRST[52][10];
char FOLLOW[52][10];

int main(){
    // 读入文法
    read_into_grammar();
    printf("Read the grammar successfully:\n");
    print_hash_table();

    // 消除左递归
    if(has_direct_left_recursion()){
        printf("The grammer has direct left recursion!\n");
        remove_direct_left_recursion();
    }
    printf("The grammer's left recursion has been removed:\n");
    print_hash_table();

    // 求FIRST集合
    compute_first();
    printf("This is the first set:\n");
    print_first();

    // 求FOLLOW集合
    compute_follow();
    printf("This is the follow set:\n");
    print_follow();

    // 构造预测分析表 
    construct_table();
    printf("This is the analysis table:\n");
    print_table();
    
    // 词法分析得到记号流
    lexical_analysis();
    printf("This is the token flow:\n");
    print_token();

    // 根据LL(1)分析表非递归预测分析token
    printf("This is the analysis process:\n");
    predictive_analytics();

    return 0;
}

void read_into_grammar(){
    // 初始化哈希表
    init_hash_table();

    // 插入文法中的产生式
    
    insert_production('E', "E+T");
    insert_production('E', "E-T");
    insert_production('E', "T");

    insert_production('T', "T*F");
    insert_production('T', "T/F");
    insert_production('T', "F");
    
    insert_production('F', "(E)");
    insert_production('F', "num");
}

int has_direct_left_recursion() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        while (p != NULL) {
            if (p->right[0] == p->left) {
                return 1;
            }
            p = p->next;
        }
    }
    return 0;
}

void remove_direct_left_recursion() {
    int flag = 0;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        
        while (p != NULL) {
            if (p->right[0] == p->left) {
                flag = 1;
                // 如果右部以左部开头，说明是左递归，需要消除
                // 创建一个新的产生式，左部是新的非终结符，右部是原来右部去掉第一个字符加上新的非终结符
                char new_left = p->left + 32; // 新的非终结符，用原来的大写字母加32得到小写字母
                strncat(p->right, &new_left, 1);
                // printf("%s\n", p->right);
                // 添加这个产生式到文法中
                insert_production(new_left, p->right + 1);
                
                // 删除原来的产生式
                delete_production(p->left, p->right);
            }
            p = p->next;
            if(p != NULL && p->right[0] != p->left && flag == 1) {
                flag = 0;
                char new_left = p->left + 32; // 新的非终结符，用原来的大写字母加32得到小写字母
                strncat(p->right, &new_left, 1);
                // insert_production(p->left, p->right + 1);
                insert_production(new_left, "");
                p = p->next;
            }
        }
    }
}

void compute_first() {
    // 遍历所有产生式
    init_first();
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        while (p != NULL) {
            // printf("%c\n", p->left);
            get_first(p->left, p->left);
            break;
        }
    }
    get_first('F', 'E');
}

void print_first() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        if (p!= NULL) {
            printf("FIRST[%c]: ", p->left);
            for (int j = 0; j < 10; j ++) {
            printf("%c", FIRST[i][j]);
            // printf("FIRST[%d][%d]", i, j);
            }
            printf("\n");
        }   
    }
    printf("\n");
}

void init_first() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        for (int j = 0; j < 10; j ++){
            // FIRST[i][j] = NULL;
        }
    }
}

void get_first(char symbol, char toadd) {
    int i;
    // symbol是要计算的非终结符
    for (i = 0; i < BUCKET_SIZE; i++) { // 遍历所有的产生式
        production* p = hash_table[i];
        while (p != NULL && p->left == symbol) {
            // 找到所有左部是symbol的产生式
            // printf("get first %c\n", p->left);
            // 产生式右部第一个是空串
            if(p->right[0] == '\0') {
                // 将空串加入FIRST(symbol)
                // printf("get ~\n");
                int m = 0;
                while(FIRST[hash(toadd)][m] != '\0') {
                    m++;
                }
                FIRST[hash(toadd)][m] = '~';
            }
            // 产生式右部第一个是非终结符
            else if(97<=p->right[0] && p->right[0] <=122 || 65<=p->right[0]&& p->right[0]<=90) {
                // printf("N:%c\n", p->right[0]);
                // printf("%d\n", p->right[0]);
                if(p->right[0] == 'n') {
                    int m = 0;
                while(FIRST[hash(toadd)][m] != '\0') {
                    if(FIRST[hash(toadd)][m] == p->right[0])
                        break;
                        m++;
                    }
                    // printf("%c FIRST[%d][%d]\n", toadd, hash(toadd), m);
                    FIRST[hash(toadd)][m] = p->right[0];
                }
                // 计算FIRST(p->right[0])，将其加入FIRST(symbol)
                get_first(p->right[0], p->left);
            }
            // 产生式右部第一个是终结符
            else {
                // 将该终结符加入FIRST(toadd)集合
                // printf("get %c\n", p->right[0]);
                int m = 0;
                while(FIRST[hash(toadd)][m] != '\0') {
                    if(FIRST[hash(toadd)][m] == p->right[0])
                        break;
                    m++;
                }
                // printf("%c FIRST[%d][%d]\n", toadd, hash(toadd), m);
                FIRST[hash(toadd)][m] = p->right[0];
            }
            p = p->next;
        }
    }
}

void compute_follow() {
    // 遍历所有非终结符
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        while (p != NULL) {
            get_follow(p->left, p->left);
            break;
        }
    }
}

void get_follow(char symbol, char toadd) {
    if(symbol == 'E') {
        FOLLOW[hash(toadd)][0] = '$';
        // 遍历所有产生式
        FOLLOW[hash(toadd)][1] = ')';
    }
    if(symbol == 'e') {
        get_follow('E', toadd);
    }
    if(symbol == 'T') {
        get_follow('E', toadd);
        add_first_to_follow('e', toadd);
    }
    if(symbol == 't') {
        get_follow('T', toadd);
    }
    if(symbol == 'F') {
        get_follow('T', toadd);
        add_first_to_follow('t', toadd);
    }
}

void add_first_to_follow(char symbol, char toadd) {
    int m = 0;
    while(FOLLOW[hash(toadd)][m] != '\0') {
        if(FIRST[hash(symbol)][0] == FOLLOW[hash(toadd)][m]) {
            break;
        }
        m++;
    }
    int n = 0;
    while(FIRST[hash(symbol)][n] != '\0') {
        if(FIRST[hash(symbol)][n] == '~') {
            n++;
            continue;
        }
        FOLLOW[hash(toadd)][m] = FIRST[hash(symbol)][n];
        m++;
        n++;
    }
}

void print_follow() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        if (p!= NULL) {
            printf("FOLLOW[%c]: ", p->left);
            for (int j = 0; j < 10; j ++) {
                printf("%c", FOLLOW[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void construct_table(){
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        while (p != NULL) {
            // 遍历所有产生式
            // printf("construct %c->%s\n", p->left, p->right);
            if(is_T(p->right[0])) {
                M[hash(p->left)][hash_T(p->right[0])] = p;
                // printf("M[%c][%c]: %c->%s\n", p->left, p->right[0], p->left, p->right);
            }
            if(p->right[0] =='n') {
                M[hash(p->left)][hash_T(p->right[0])] = p;
                // printf("M[%c][%c]: %c->%s\n", p->left, p->right[0], p->left, p->right);
            }
            for(int j = 0; FIRST[hash(p->right[0])][j] != '\0'; j++) {
                char a = FIRST[hash(p->right[0])][j];
                // printf("a: %c\n", a);
                // printf("%d\n", hash_T(a));
                M[hash(p->left)][hash_T(a)] = p;
                // printf("M[%c][%c]: %c->%s\n", p->left, a, p->left, p->right);
            }
            if(has_epsilon(p->left)) {
                for (int m = 0; FOLLOW[hash(p->left)][m] != '\0'; m++) {
                    char b = FOLLOW[hash(p->left)][m];
                    M[hash(p->left)][hash_T(b)] = p;
                    // printf("epsilon M[%c][%c]: %c->%s\n", p->left, b, p->left, p->right);
                }
            }
            p = p->next;
        }
    }
}

int is_T(char c) {
    if(c == 'n') {
        return 1;
    }
    if(97<=c&&c<=122 || 65<=c&&c<=90 || c =='\0') {
        return 0;
    }
    return 1;
}
int hash_T(char c) {
    if(c == 'n') {
        return 0;
    }
    else if(c == '+') {
        return 1;
    }
    else if(c == '-') {
        return 2;
    }
    else if(c == '*') {
        return 3;
    }
    else if(c == '/') {
        return 4;
    }
    else if(c == '(') {
        return 5;
    }
    else if(c == ')') {
        return 6;
    }
    else if(c == '$') {
        return 7;
    }
}

void print_table() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        if (p!= NULL) {
            printf("M[%c]: \n", p->left);
            for (int j = 0; j < 10; j ++) {
                if(M[i][j] == NULL){
                    continue;
                }
                printf("M[%c][%c]:%c->%s\n", p->left, inverse_hash_T(j), M[i][j]->left, M[i][j]->right);
            }
            printf("\n");
        }
    }
}

char inverse_hash_T(int n) {
    if(n == 0) {
        return 'n';
    }
    else if(n == 1) {
        return '+';
    }
    else if(n == 2) {
        return '-';
    }
    else if(n == 3) {
        return '*';
    }
    else if(n == 4) {
        return '/';
    }
    else if(n == 5) {
        return '(';
    }
    else if(n == 6) {
        return ')';
    }
    else if(n == 7) {
        return '$';
    }
}

int has_epsilon(char c) {
    for(int i = 0; FIRST[hash(c)][i] != '\0'; i++) {
        if(FIRST[hash(c)][i] == '~') {
            return 1;
        }
    }
    return 0;
}

void predictive_analytics() {
    FILE *fp; // 定义一个文件指针
    fp = fopen("output.txt", "w"); // 打开一个输出文件，如果不存在则创建，如果存在则覆盖
    if (fp == NULL) { // 如果打开失败
        printf("无法打开文件\n"); // 输出错误信息
        return; // 返回非零值，表示程序异常退出
    }
    // 完成输入字符串和分析栈的初始化
    int size = 100; // 定义栈的最大容量为100
    Stack *s = init(size); // 初始化栈
    push(s, '$');
    push(s, 'E');

    int len = strlen(token); // 获取字符串token的长度
    // printf("len: %d\n", len);
    token[len] = '$'; // 在字符串token的末尾添加$符号
    token[len + 1] = '\0'; // 在字符串token的最后添加空字符，表示字符串的结束


    len = strlen(token);
    char* c = token;
    char e;
    top(s, &e);
    while (e != '$') {
        // printf("analysis: %c, %c\n", e, c);
        do_one_analysis(s, &c, fp); // 根据栈顶元素和当前分析字符完成一次分析
        top(s, &e);
    }
    print_stack(s);
    printf(" Token: ");
    printf("%s\n", c);
    printf("ACC\n");
    fclose(fp); // 关闭文件
}

void do_one_analysis(Stack *s, char **c, FILE *fp) {

    print_stack(s);
    printf(" Token: ");
    printf("%s\n", *c);

    char m;
    top(s, &m); // m 是栈顶符号，*c是ip指向的符号
    if(is_T(m) || m == '$') {
        if (m == **c) {
            pop(s, &m); // 将栈顶弹出
            *c = *c + 1; 
            // printf("c:%c\n", *c);
            // c++; // ip指针前移一个位置
        }
    }
    else {
        production* p = M[hash(m)][hash_T(**c)];
        if(p != NULL) {
            pop(s, &m);// 将栈顶弹出
            // 将p->right反向压入栈
            int len = strlen(p->right);
            if(p->right[0] == 'n') {
                push(s, 'n');
                printf("%c->%s\n", p->left, p->right); // 输出产生式
                fprintf(fp, "%c->%s\n", p->left, p->right); // 将产生式的格式化字符串写入文件
                return;
            }
            for (int i = len-1; i >= 0; i--) { // 遍历字符串中的每个字符
                
                push(s, p->right[i]); // 将字符压入栈顶
            }
            printf("%c->%s\n", p->left, p->right); // 输出产生式
            fprintf(fp, "%c->%s\n", p->left, p->right); // 将产生式的格式化字符串写入文件
        }
    }

}