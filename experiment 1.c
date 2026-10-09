#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Token categories
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

// List of C reserved keywords
const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", 
    "while", "for", "return", "void", "struct"
};
const int NUM_KEYWORDS = 11;

// Helper to check if a string matches a keyword
bool is_keyword(const char *str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

// Convert enum to readable string
const char* get_token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_KEYWORD:    return "KEYWORD";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_NUMBER:     return "NUMBER";
        case TOKEN_OPERATOR:   return "OPERATOR";
        case TOKEN_DELIMITER:  return "DELIMITER";
        default:               return "UNKNOWN";
    }
}

// Core Lexical Analyzer function
void analyze(const char *code) {
    int i = 0;
    int len = strlen(code);

    printf("%-20s | %s\n", "LEXEME", "TOKEN TYPE");
    printf("----------------------------------------\n");

    while (i < len) {
        // 1. Skip whitespace (spaces, tabs, newlines)
        if (isspace(code[i])) {
            i++;
            continue;
        }

        // 2. Ignore single-line comments (//)
        if (code[i] == '/' && i + 1 < len && code[i + 1] == '/') {
            while (i < len && code[i] != '\n') i++;
            continue;
        }

        // 3. Match Identifiers and Keywords ([a-zA-Z_][a-zA-Z0-9_]*)
        if (isalpha(code[i]) || code[i] == '_') {
            char buffer[64];
            int b_idx = 0;

            while (i < len && (isalnum(code[i]) || code[i] == '_')) {
                if (b_idx < 63) buffer[b_idx++] = code[i];
                i++;
            }
            buffer[b_idx] = '\0';

            TokenType type = is_keyword(buffer) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
            printf("%-20s | %s\n", buffer, get_token_type_name(type));
            continue;
        }

        // 4. Match Integer and Floating-Point Numbers
        if (isdigit(code[i])) {
            char buffer[64];
            int b_idx = 0;

            while (i < len && (isdigit(code[i]) || code[i] == '.')) {
                if (b_idx < 63) buffer[b_idx++] = code[i];
                i++;
            }
            buffer[b_idx] = '\0';

            printf("%-20s | %s\n", buffer, get_token_type_name(TOKEN_NUMBER));
            continue;
        }

        // 5. Match Operators (Handles 1 and 2-character operators like ==, <=, ++, &&)
        if (strchr("+-*/%=<>!&|", code[i])) {
            char buffer[3] = {code[i], '\0', '\0'};

            if (i + 1 < len && strchr("=+-&|", code[i + 1])) {
                buffer[1] = code[i + 1];
                i++;
            }
            i++;

            printf("%-20s | %s\n", buffer, get_token_type_name(TOKEN_OPERATOR));
            continue;
        }

        // 6. Match Delimiters
        if (strchr(";,(){}\\[\\]", code[i])) {
            char buffer[2] = {code[i], '\0'};
            i++;

            printf("%-20s | %s\n", buffer, get_token_type_name(TOKEN_DELIMITER));
            continue;
        }

        // 7. Unknown / Unrecognized character
        char unknown[2] = {code[i], '\0'};
        printf("%-20s | %s\n", unknown, get_token_type_name(TOKEN_UNKNOWN));
        i++;
    }
}

int main() {
    // Sample input source code snippet
    const char *source_code = 
        "int main() {\n"
        "    // Declare variables\n"
        "    float total_sum = 10.5 + 20;\n"
        "    if (total_sum >= 30) {\n"
        "        return 1;\n"
        "    }\n"
        "}";

    printf("Input Code:\n%s\n\n", source_code);
    analyze(source_code);

    return 0;
}
