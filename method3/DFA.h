// DFA状态
enum DFAState {
    STATE_0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_5,
    STATE_6,
    STATE_7,
    STATE_8,
    STATE_9,
    STATE_10,
    STATE_11,
    STATE_12,
    STATE_13,
    STATE_14,
    STATE_15,
    STATE_ACC,
    STATE_ERROR,
    NUM_STATES
};

// 定义项目
struct Item {
    char left;
    char right[10];
    int dotPosition;
};

// 定义状态
struct State {
    struct Item items[10];
    int numItems;
};

struct State state[16];
// 输入字符
enum Input {
    INPUT_PLUS,
    INPUT_MINUS,
    INPUT_MULTIPLY,
    INPUT_DIVIDE,
    INPUT_LEFT_PARENTHESIS,
    INPUT_RIGHT_PARENTHESIS,
    INPUT_NUM,
    INPUT_DOLLAR,
    INPUT_E,
    INPUT_T,
    INPUT_F,
    NUM_INPUTS
};

void initializeState(struct State* state, struct Item items[], int numItems); // 初始化状态
void printState(struct State* state); // 打印状态
void ConstructDFA(); // 构造DFA
void printItem(struct State* state, int num); // 打印对应编号的项目
struct Item getItem(struct State* state, int num); // 获取对应编号的项目