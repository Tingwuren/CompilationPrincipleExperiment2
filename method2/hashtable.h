typedef struct production {  
    char left; // 左部非终结符
    char* right; // 右部符号串
    struct production *next; // 相同非终结符下一产生式
} production;

#define BUCKET_SIZE 52 // 假设哈希表的大小为26，即非终结符的个数
#define MAX_LENGTH 10 // 假设产生式右部的最大长度为10

extern production* hash_table[BUCKET_SIZE]; // 哈希表是一个指向产生式的指针数组
extern production* M[52][10]; // LL1分析表
int hash(char c); // 哈希函数定义
void init_hash_table(); // 初始化哈希表，将所有指针设为NULL
void insert_production(char left, char* right); // 插入一个产生式到哈希表中，如果已经存在，则忽略
production* find_production(char left, char* right); // 查找一个产生式是否在哈希表中，如果存在，则返回指向该产生式的指针，否则返回NULL
void delete_production(char left, char* right); // 删除一个产生式从哈希表中，如果不存在，则忽略
void print_hash_table(); // 打印哈希表的内容