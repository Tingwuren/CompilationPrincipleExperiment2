// 定义栈的结构体类型
typedef struct Stack {
    char *data; // 数据数组
    int top; // 栈顶指针
    int max_size; // 栈的最大容量
} Stack;

Stack *init(int size);
int is_empty(Stack *s);
int is_full(Stack *s);
int push(Stack *s, char e);
int pop(Stack *s, char *e);
int top(Stack *s, char *e);
void clear(Stack *s);
void print_stack(Stack *s);

