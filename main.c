#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CharStack.c"

// Returns the position (1-indexed) in the array
// where the opening and closing parentheses dont match
// Returns 0 if all of them are matched
int find_parentheses_mismatch(char *parens, size_t len) {
    char buffer[len];
    Stack stack = stk_init(buffer);

    char tmp;
    for (size_t i = 0; i < len; i++) {
        if (parens[i] == '(')
            stk_push(&stack, parens[i]);
        else if (parens[i] == ')') {
            // Checks and returns index of an extra closing parentheses
            tmp = stk_pop(&stack);
            if (tmp == '\0') {
                return i+1;
            }
        }
    }
    
    // Returns index of an extra opening parentheses
    // which should always be at the first location
    // Otherwise returns 0
    tmp = stk_pop(&stack);
    if (tmp != '\0')
        return -1;

    return 0;
}


int main(int argc, char** argv) {
    argv++;
    char *str = *argv;
    
    const int size = strlen(str);
    char parens[size];
    int j = 0;
    for(int i=0; i<size; i++) {
        if (str[i] == '(' || str[i] == ')')
            parens[j++] = str[i];
    }
    parens[j] = '\0'; 
    printf("%s\n", parens);    

    int index = find_parentheses_mismatch(parens, j);
    if (index) {
        fprintf(stderr, "Mismatched Parentheses at index: %d\n", index);
        exit(1);
    }

    putchar('\n');
    return 0;
}
