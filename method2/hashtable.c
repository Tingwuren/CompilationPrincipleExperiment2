#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "LL1.h"
#include "hashtable.h"

int hash(char c) {
    // 如果c是大写字母，就用ASCII码减去65作为哈希值
    if (c >= 'A' && c <= 'Z') {
        return c - 65;
    }
    // 如果c是小写字母，就用ASCII码减去97再加上26作为哈希值
    else if (c >= 'a' && c <= 'z') {
        return c - 97 + 26;
    }
    // 如果都不是，就返回-1表示无效的输入
    else {
        return -1;
    }
};

// 初始化哈希表，将所有指针设为NULL
void init_hash_table() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

// 插入一个产生式到哈希表中，如果已经存在，则忽略
void insert_production(char left, char* right) {
    int index = hash(left); // 计算左部非终结符的哈希值
    production* p = hash_table[index]; // 获取哈希表中对应的指针
    production* prev = NULL; // 用来记录前一个指针
    
    if(p == NULL) {
        // printf("hashtable is NULL\n");
        production* n = (production*)malloc(sizeof(production)); // 分配内存空间
        n->left = left; // 设置左部非终结符
        n->right = (char*)malloc(MAX_LENGTH * sizeof(char)); // 分配内存空间
        strcpy(n->right, right); // 设置右部符号串
        n->next = NULL;
        hash_table[index] = n;
        return;
    }
    while (p != NULL) {
        // 如果产生式已经存在，则直接返回
        if (p->left == left && strcmp(p->right, right) == 0) {
            return;
        }
        // 否则，沿着链表继续查找
        prev = p;
        p = p->next;
    }
    // 如果产生式不存在，则创建一个新的结点，并插入到链表的头部
    production* n = (production*)malloc(sizeof(production)); // 分配内存空间
    n->left = left; // 设置左部非终结符
    n->right = (char*)malloc(MAX_LENGTH * sizeof(char)); // 分配内存空间
    strcpy(n->right, right); // 设置右部符号串
    n->next = NULL;
    prev->next = n;
    // p->next = hash_table[index]; // 设置下一个指针
    // hash_table[index] = p; // 更新哈希表中的指针
    
}

// 查找一个产生式是否在哈希表中，如果存在，则返回指向该产生式的指针，否则返回NULL
production* find_production(char left, char* right) {
    int index = hash(left); // 计算左部非终结符的哈希值
    production* p = hash_table[index]; // 获取哈希表中对应的指针
    while (p != NULL) {
        // 如果产生式存在，则返回指针
        if (p->left == left && strcmp(p->right, right) == 0) {
            return p;
        }
        // 否则，沿着链表继续查找
        p = p->next;
    }
    // 如果产生式不存在，则返回NULL
    return NULL;
}

// 删除一个产生式从哈希表中，如果不存在，则忽略
void delete_production(char left, char* right) {
    int index = hash(left); // 计算左部非终结符的哈希值
    production* p = hash_table[index]; // 获取哈希表中对应的指针
    production* prev = NULL; // 用来记录前一个指针
    while (p != NULL) {
        // 如果产生式存在，则删除结点，并更新哈希表中的指针
        if (p->left == left && strcmp(p->right, right) == 0) {
            if (prev == NULL) {
                // 如果是链表的头部，则直接更新哈希表中的指针
                hash_table[index] = p->next;
            } else {
                // 如果不是链表的头部，则更新前一个指针的next域
                prev->next = p->next;
            }
        // 释放内存空间
        free(p->right);
        free(p);
        return;
        }
        // 否则，沿着链表继续查找，并记录前一个指针
        prev = p;
        p = p->next;
    }
    // 如果产生式不存在，则直接返回
    return;
}

// 打印哈希表的内容
void print_hash_table() {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        production* p = hash_table[i];
        // printf("Bucket %d: ", i);
        while (p != NULL) {
            printf("[%c -> %s] ", p->left, p->right);
            p = p->next;
            printf("\n");
        }
        // printf("\n");
    }
    printf("\n");
}