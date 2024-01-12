int Goto[16][3] = {
    //E T F
    //STATE_0
    {1, 2, 3},
    //STATE_1
    {-1, -1, -1},
    //STATE_2
    {-1, -1, -1},
    //STATE_3
    {-1, -1, -1},
    //STATE_4
    {10, 2, 3},
    //STATE_5
    {-1, -1, -1},
    //STATE_6
    {-1, 11, 3},
    //STATE_7
    {-1, 12, 3},
    //STATE_8
    {-1, -1, 13},
    //STATE_9
    {-1, -1, 14},
    //STATE_10
    {-1, -1, -1},
    //STATE_11
    {-1, -1, -1},
    //STATE_12
    {-1, -1, -1},
    //STATE_13
    {-1, -1, -1},
    //STATE_14
    {-1, -1, -1},
    //STATE_15
    {-1, -1, -1}
};
char* Action[16][8] = {
    //+    -    *    /    (    )    n    $
    // STATE_0
    {"ER","ER","ER","ER","S4","ER","S5","ER"},
    // STATE_1
    {"S6","S7","ER","ER","ER","ER","ER","ACC"},
    // STATE_2
    {"R3","R3","S8","S9","ER","R3","ER","R3"},
    // STATE_3
    {"R6","R6","R6","R6","ER","R6","ER","R6"},
    // STATE_4
    {"ER","ER","ER","ER","S4","ER","S5","ER"},
    // STATE_5
    {"R8","R8","R8","R8","ER","R8","ER","R8"},
    // STATE_6
    {"ER","ER","ER","ER","S4","ER","S5","ER"},
    // STATE_7
    {"ER","ER","ER","ER","S4","ER","S5","ER"},
    // STATE_8
    {"ER","ER","ER","ER","S4","ER","S5","ER"},
    // STATE_9
    {"ER","ER","ER","ER","S4","ER","S5","ER"},
    // STATE_10
    {"S6","S7","ER","ER","ER","S15","ER","ER"},
    // STATE_11
    {"R1","R1","S8","S9","ER","R1","ER","R1"},
    // STATE_12
    {"R2","R2","S8","S9","ER","R2","ER","R2"},
    // STATE_13
    {"R4","R4","R4","R4","ER","R4","ER","R4"},
    // STATE_14
    {"R5","R5","R5","R5","ER","R5","ER","R5"},
    // STATE_15
    {"R7","R7","R7","R7","ER","R7","ER","R7"}
};

void ConstructTable(); // 构造SLR1分析表
void analysis_process();
int do_one_analysis(Stack *status,  Stack *symbol,char **c, FILE *fp);
int hash_a(char c);
int hash_A(char c);
char* get_right(int num);
char get_left(int num);
