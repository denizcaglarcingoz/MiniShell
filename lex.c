#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Token types
enum {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END
};

// Token structure
typedef struct {
    int type;
    int value;
} Token;

// Function to tokenize input string
Token getToken(char **input) {
    Token token = {0};

    // Skip whitespace
    while (isspace(**input)) {
        (*input)++;
    }

    // Check for end of input
    if (**input == '\0') {
        token.type = END;
        return token;
    }

    // Parse number
    if (isdigit(**input)) {
        token.type = NUMBER;
        token.value = strtol(*input, input, 10);
        printf("token type is number and value %d\n", token.value);
        return token;
    }

    // Parse other operators
    switch (**input) {
        case '+': token.type = PLUS; break;
        case '-': token.type = MINUS; break;
        case '*': token.type = MULTIPLY; break;
        case '/': token.type = DIVIDE; break;
        case '(': token.type = LPAREN; break;
        case ')': token.type = RPAREN; break;
        default:
            fprintf(stderr, "Unknown character: %c\n", **input);
            exit(1);
    }
    printf("Token Type is %d\n", token.type);
    (*input)++;
    return token;
}

// Recursive descent parser
int expr(char **input);

int factor(char **input) {
    Token token = getToken(input);
    int result;

    switch (token.type) {
        case NUMBER: result = token.value; break;
        case LPAREN:
            result = expr(input);
            if (getToken(input).type != RPAREN) {
                fprintf(stderr, "Mismatched parentheses\n");
                exit(1);
            }
            break;
        default:
            fprintf(stderr, "Syntax error\n");
            exit(1);
    }

    return result;
}

int term(char **input) {
    int result = factor(input);

    Token token;
    while ((token = getToken(input)).type == MULTIPLY || token.type == DIVIDE || token.type == PLUS || token.type == MINUS) {
        int nextFactor = factor(input);
        
        if (token.type == PLUS) {
            printf("plus\n");
            result += nextFactor;
            break;
        }
        
        if (token.type == MINUS) {
            printf("minus\n");
            result -= nextFactor;
            break;
        }

        if (token.type == MULTIPLY) {
            printf("multiply\n");
            result *= nextFactor;
        } else {
            if (nextFactor == 0) {
                fprintf(stderr, "Error: Division by zero\n");
                exit(1);
            }
            result /= nextFactor;
        }
    }
    return result;
}

int expr(char **input) {
    int result = term(input);
    Token token;
    token = getToken(input);
    return result;
}

int main() {
    char input[100];
    printf("Enter expression: ");
    fgets(input, sizeof(input), stdin);

    char *ptr = input;
    int result = expr(&ptr);
    printf("Result: %d\n", result);
    return 0;
}