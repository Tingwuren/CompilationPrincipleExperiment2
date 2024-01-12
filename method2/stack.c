#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


// 初始化栈，分配内存空间，返回栈的指针
Stack *init(int size) {
    Stack *s = (Stack *)malloc(sizeof(Stack)); // 分配栈的内存空间
    s->data = (char *)malloc(sizeof(int) * size); // 分配数据数组的内存空间
    s->top = -1; // 初始化栈顶指针为-1，表示空栈
    s->max_size = size; // 记录栈的最大容量
    return s;
}

// 判断栈是否为空，返回1表示空，0表示非空
int is_empty(Stack *s) {
    return s->top == -1;
}

// 判断栈是否已满，返回1表示满，0表示未满
int is_full(Stack *s) {
    return s->top == s->max_size - 1;
}

// 入栈，将元素e压入栈顶，成功返回1，失败返回0
int push(Stack *s, char e) {
    if (is_full(s)) { // 如果栈已满，无法入栈
        printf("Stack is full!\n");
        return 0;
    }
    s->top++; // 栈顶指针加1
    s->data[s->top] = e; // 将元素e存入栈顶位置
    return 1;
}

// 出栈，将栈顶元素弹出，并用e返回，成功返回1，失败返回0
int pop(Stack *s, char *e) {
    if (is_empty(s)) { // 如果栈为空，无法出栈
        printf("Stack is empty!\n");
        return 0;
    }
    *e = s->data[s->top]; // 将栈顶元素赋值给e
    s->top--; // 栈顶指针减1
    return 1;
}

// 获取栈顶元素，不弹出，用e返回，成功返回1，失败返回0
int top(Stack *s, char *e) {
    if (is_empty(s)) { // 如果栈为空，无法获取栈顶元素
        printf("Stack is empty!\n");
        return 0;
    }
    *e = s->data[s->top]; // 将栈顶元素赋值给e
    return 1;
}

// 清空栈，释放内存空间
void clear(Stack *s) {
    if (s == NULL) return; // 如果栈为空，直接返回
    free(s->data); // 释放数据数组的内存空间
    free(s); // 释放栈的内存空间
    return;
}

// 打印栈，从栈顶到栈底的顺序
void print_stack(Stack *s) {
    printf("Stack: [");
    for (int i = 0; i <= s->top; i++) { // 从栈底到栈顶遍历数据数组
        printf("%c", s->data[i]); // 打印每个元素
        if (i < s->top) printf(", "); // 如果不是最后一个元素，打印逗号分隔
    }
    printf("]");
    // printf("\n");
    return;
}