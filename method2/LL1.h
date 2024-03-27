void read_into_grammar(); // 将文法读入哈希表
int has_direct_left_recursion(); // 判断一个文法是否含有直接左递归
void remove_direct_left_recursion(); // 消除一个文法的直接左递归
extern char FIRST[52][10];
void compute_first(); // 计算文法的FIRST集合
void print_first(); //打印FIRST集合
void init_first();
void get_first(char symbol, char toadd);
extern char FOLLOW[52][10];
void compute_follow();
void get_follow(char symbol, char toadd);
void add_first_to_follow(char symbol, char toadd);
void print_follow();
int hash_T(char c);
char inverse_hash_T(int n);
int is_T(char c);


void construct_table();
void print_table();
int has_epsilon(char c);

void predictive_analytics(); // 根据LL(1)分析表非递归预测分析token
void do_one_analysis(Stack *s, char **c, FILE *fp);