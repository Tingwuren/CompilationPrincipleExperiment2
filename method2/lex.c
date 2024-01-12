#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lex.h"
void lexical_analysis() {
    // 读入输入文件input.txt，将字符串存储在s中
    FILE *fp; // 文件指针
    fp = fopen("input.txt", "r"); // 打开输入文件
    if (fp == NULL) { // 如果打开失败
        printf("无法打开文件\n"); // 输出错误信息
        exit(1); // 退出程序
    }
    fgets(s, 100, fp); // 从文件中读取一行字符串，存储在s中
    printf("This is the string:\n");
    printf("%s", s);
    fclose(fp); // 关闭文件
    
    int i = 0; // 输入字符串的索引
    int j = 0; // 输出字符串的索引
    char c; // 当前字符
    while ((c = s[i++]) != '\n'&& c != '\0') { // 从左到右扫描输入字符串，直到遇到空字符
        if (isdigit(c)) { // 如果当前字符是数字
            token[j++] = 'n'; // 输出字符串添加一个n
            while (isdigit(s[i])) i++; // 跳过后续的数字
        } else { // 如果当前字符不是数字
            token[j++] = c; // 输出字符串添加当前字符
        }
    }
    token[j] = '\0'; // 输出字符串添加空字符
}

void print_token() {
    printf("%s\n", token); // 输出token
    printf("\n");
}