#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CharStack.c"

// Returns the position (1-indexed) in the array
// where the opening and closing parentheses dont match
// Returns 0 if they all match
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


int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '(':
        default:
            return 0;
    }
}

// Converts an infix expression to postfix
// a b c * + == a + (b * c) 
void infix_to_postfix(char *infix_str, char *postfix_str, size_t len) {
    char buffer[len];
    Stack stack = stk_init(buffer);

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char ch = infix_str[i];
        // checks for operators (a to z and A to Z)
        if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90) {
            postfix_str[j++] = ch;
        }
        // checks for operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (precedence(stack.data[stack.top]) >= precedence(ch)) {
                postfix_str[j++] = stk_pop(&stack);
            }
            stk_push(&stack, ch);
        }
        // checks for opening parentheses
        else if (ch == '(') {
            stk_push(&stack, ch);
        }
        // checks for closing parentheses
        else if (ch == ')') {
            char tmp;
            while ((tmp = stk_pop(&stack)) != '(') {
                postfix_str[j++] = tmp;
            }
        }
    }

    // Empty out the stack
    while (stack.top != -1) {
        char ch = stk_pop(&stack);
        postfix_str[j++] = ch;
    }
    postfix_str[j] = '\0';
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

    char postfix[size];
    infix_to_postfix(str, postfix, size);
    printf("%s\n", postfix);

    putchar('\n');
    return 0;
}
