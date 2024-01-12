#include <stdio.h>
#include "DFA.h"

// 初始化状态
void initializeState(struct State* state, struct Item items[], int numItems) {
    for (int i = 0; i < numItems; i++) {
        state->items[i] = items[i];
    }
    state->numItems = numItems;
}

// 打印状态
void printState(struct State* state) {
    for (int i = 0; i < state->numItems; i++) {
        printf("%c -> ", state->items[i].left);
        for (int j = 0; j < 10; j++) {
            if (j == state->items[i].dotPosition) {
                printf(".");
            }
            printf("%c", state->items[i].right[j]);
        }
        printf("\n");
    }
}

void printItem(struct State* state, int num) {
    printf("%c -> ", state->items[num].left);
    for (int j = 0; j < 10; j++) {
        if (j == state->items[num].dotPosition) {
            printf(".");
        }
        printf("%c", state->items[num].right[j]);
    }
    printf("\n");
}
struct Item getItem(struct State* state, int num) {
    struct Item item = state->items[num];
    return item;
}
// DFA当前状态
enum DFAState currentState = STATE_0;

// 构造DFA
void ConstructDFA() {
    // 初始化STATE_0
    struct Item items0[] = {
        {'S', "E", 0},
        {'E', "E+T", 0},
        {'E', "E-T", 0},
        {'E', "T", 0},
        {'T', "T*F", 0},
        {'T', "T/F", 0},
        {'T', "F", 0},
        {'F', "(E)", 0},
        {'F', "n", 0}
    };
    initializeState(&state[0], items0, sizeof(items0) / sizeof(struct Item));
    // 打印状态
    // printState(&state[0]);

    // 初始化STATE_1
    struct Item items1[] = {
        {'E', "E", 1},
        {'E', "E+T", 1},
        {'E', "E-T", 1}
    };
    initializeState(&state[1], items1, sizeof(items1) / sizeof(struct Item));
    // printState(&state[1]); // 打印状态

    // 初始化STATE_2
    struct Item items2[] = {
        {'E', "T", 1},
        {'T', "T*F", 1},
        {'T', "T/F", 1}
    };
    initializeState(&state[2], items2, sizeof(items2) / sizeof(struct Item));
    // printState(&state[2]); // 打印状态

    // 初始化STATE_3
    struct Item items3[] = {
        {'T', "F", 1}
    };
    initializeState(&state[3], items3, sizeof(items3) / sizeof(struct Item));
    // printState(&state[3]); // 打印状态

    // 初始化STATE_4
    struct Item items4[] = {
        {'F', "(E)", 1},
        {'E', "E+T", 0},
        {'E', "E-T", 0},
        {'E', "T", 0},
        {'T', "T*F", 0},
        {'T', "T/F", 0},
        {'T', "F", 0},
        {'F', "(E)", 0},
        {'F', "n", 0}
    };
    initializeState(&state[4], items4, sizeof(items4) / sizeof(struct Item));
    // printState(&state[4]); // 打印状态

    // 初始化STATE_5
    struct Item items5[] = {
        {'F', "n", 1}
    };
    initializeState(&state[5], items5, sizeof(items5) / sizeof(struct Item));
    // printState(&state[5]); // 打印状态

    // 初始化STATE_6
    struct Item items6[] = {
        {'E', "E+T", 2},
        {'T', "T*F", 0},
        {'T', "T/F", 0},
        {'T', "F", 0},
        {'F', "(E)", 0},
        {'F', "n", 0}
    };
    initializeState(&state[6], items6, sizeof(items6) / sizeof(struct Item));
    // printState(&state[6]); // 打印状态

    // 初始化STATE_7
    struct Item items7[] = {
        {'E', "E-T", 2},
        {'T', "T*F", 0},
        {'T', "T/F", 0},
        {'T', "F", 0},
        {'F', "(E)", 0},
        {'F', "n", 0}
    };
    initializeState(&state[7], items7, sizeof(items7) / sizeof(struct Item));
    // printState(&state[7]); // 打印状态

    // 初始化STATE_8
    struct Item items8[] = {
        {'T', "T*F", 2},
        {'F', "(E)", 0},
        {'F', "n", 0}
    };
    initializeState(&state[8], items8, sizeof(items8) / sizeof(struct Item));
    // printState(&state[8]); // 打印状态

    // 初始化STATE_9
    struct Item items9[] = {
        {'T', "T/F", 2},
        {'F', "(E)", 0},
        {'F', "n", 0}
    };
    initializeState(&state[9], items9, sizeof(items9) / sizeof(struct Item));
    // printState(&state[9]); // 打印状态

    // 初始化STATE_10
    struct Item items10[] = {
        {'F', "(E)", 2},
        {'E', "E+T", 1},
        {'E', "E-T", 1}
    };
    initializeState(&state[10], items10, sizeof(items10) / sizeof(struct Item));
    // printState(&state[10]); // 打印状态

    // 初始化STATE_11
    struct Item items11[] = {
        {'E', "E+T", 3},
        {'T', "T*F", 1},
        {'T', "T/F", 1}
    };
    initializeState(&state[11], items11, sizeof(items11) / sizeof(struct Item));
    // printState(&state[11]); // 打印状态

    // 初始化STATE_12
    struct Item items12[] = {
        {'E', "E-T", 3},
        {'T', "T*F", 1},
        {'T', "T/F", 1}
    };
    initializeState(&state[12], items12, sizeof(items12) / sizeof(struct Item));
    // printState(&state[12]); // 打印状态

    struct Item items13[] = {
        {'T', "T*F", 3}
    };
    initializeState(&state[13], items13, sizeof(items13) / sizeof(struct Item));
    // printState(&state[13]); // 打印状态

    struct Item items14[] = {
        {'T', "T/F", 3}
    };
    initializeState(&state[14], items14, sizeof(items14) / sizeof(struct Item));
    // printState(&state[14]); // 打印状态

    struct Item items15[] = {
        {'T', "(E)", 3}
    };
    initializeState(&state[15], items15, sizeof(items15) / sizeof(struct Item));
    // printState(&state[15]); // 打印状态
}
