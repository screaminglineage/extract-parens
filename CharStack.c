typedef struct {
    char *data;
    size_t top;
} Stack;

// Initializes top of stack to -1
// which signals that the stack is empty
Stack stk_init(char *arr) {
    Stack s = { arr, -1 };
    return s;
}

// Pushes char onto stack
void stk_push(Stack *stack, char ch) {
    stack->top++;
    stack->data[stack->top] = ch;
}

// Pops topmost value from the stack
// Returns '\0' if empty
char stk_pop(Stack *stack) {
    if (stack->top == -1) 
        return '\0';
    
    char val = stack->data[stack->top];
    stack->top--;
    return val;
}



