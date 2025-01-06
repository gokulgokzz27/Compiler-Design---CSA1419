#include <string.h>
#include <ctype.h>
#include <stdio.h>

void keyword(char str[10]) {
    if (strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 || 
        strcmp("int", str) == 0 || strcmp("float", str) == 0 || strcmp("char", str) == 0 || 
        strcmp("double", str) == 0 || strcmp("static", str) == 0 || strcmp("switch", str) == 0 || 
        strcmp("case", str) == 0) {
        printf("\n%s is a keyword", str);
    } else {
        printf("\n%s is an identifier", str);
    }
}

int main() {
    FILE *f1, *f2, *f3;
    char c, str[10];
    int num[100], lineno = 1, tokenvalue = 0, i = 0, j = 0, k = 0;

    printf("\nEnter the C program (Press CTRL+D to end input):\n");
    f1 = fopen("input", "w");
    if (f1 == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    
    // Input loop to capture C program until CTRL+D (EOF)
    while ((c = getchar()) != EOF) {
        putc(c, f1);  // Write to file
        printf("%c", c);  // Debugging: Output characters read
    }
    fclose(f1);

    // Open the input file for reading
    f1 = fopen("input", "r");
    f2 = fopen("identifier", "w");
    f3 = fopen("specialchar", "w");

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Error opening files for reading or writing.\n");
        return 1;
    }

    // Read the input program and process tokens
    while ((c = getc(f1)) != EOF) {
        if (isdigit(c)) {
            tokenvalue = c - '0';
            c = getc(f1);
            while (isdigit(c)) {
                tokenvalue = tokenvalue * 10 + (c - '0');
                c = getc(f1);
            }
            num[i++] = tokenvalue;  // Save numbers
            ungetc(c, f1);
        } else if (isalpha(c)) {
            putc(c, f2);
            c = getc(f1);
            while (isdigit(c) || isalpha(c) || c == '_' || c == '$') {
                putc(c, f2);
                c = getc(f1);
            }
            putc(' ', f2);
            ungetc(c, f1);
        } else if (c == ' ' || c == '\t') {
            // Ignore spaces and tabs
        } else if (c == '\n') {
            lineno++;  // Count the number of lines
        } else {
            putc(c, f3);
        }
    }

    fclose(f2);
    fclose(f3);
    fclose(f1);

    // Output the numbers found in the program
    printf("\nThe numbers in the program are: ");
    for (j = 0; j < i; j++) {
        printf("%d ", num[j]);
    }
    printf("\n");

    // Process keywords and identifiers
    f2 = fopen("identifier", "r");
    k = 0;
    printf("\nThe keywords and identifiers are: ");
    while ((c = getc(f2)) != EOF) {
        if (c != ' ') {
            str[k++] = c;
        } else {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }
    fclose(f2);

    f3 = fopen("specialchar", "r");
    printf("\nSpecial characters are: ");
    while ((c = getc(f3)) != EOF) {
        printf("%c", c);
    }
    printf("\n");
    fclose(f3);
    printf("Total number of lines are: %d\n", lineno);

    return 0; 
}

