#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
char grammar[MAX][MAX] = {
    "E->TX",
    "X->+TX",
    "X->",
    "T->FY",
    "Y->*FY",
    "Y->",
    "F->(E)",
    "F->id"
};
char parsingTable[3][3][MAX] = {
    {"TX", "", ""},
    {"+TX", "e", "e"},
    {"FY", "", "e"}
};

int isTerminal(char symbol) {
    return !(symbol >= 'A' && symbol <= 'Z');
}

void parse(char *input) {
    char stack[MAX];
    int top = -1;
    int i = 0, j;
    stack[++top] = 'E';

    while (top != -1) {
        char symbol = stack[top--];
        if (isTerminal(symbol)) {
            if (symbol == input[i]) {
                i++;
            } else {
                printf("Error: Unexpected symbol %c\n", input[i]);
                return;
            }
        } else {
            int row = symbol - 'E';
            int col = (input[i] == 'id') ? 0 : (input[i] == '+') ? 1 : (input[i] == '*') ? 2 : -1;
            if (col != -1) {
                char *production = parsingTable[row][col];
                for (j = strlen(production) - 1; j >= 0; j--) {
                    stack[++top] = production[j];
                }
            } else {
                printf("Error: No rule for symbol %c\n", symbol);
                return;
            }
        }
    }

    if (input[i] == '\0') {
        printf("Input string is successfully parsed.\n");
    } else {
        printf("Error: Remaining input symbols.\n");
    }
}

int main() {
    char input[MAX];
    printf("Enter input string: ");
    scanf("%s", input);

    parse(input);

    return 0;
}

