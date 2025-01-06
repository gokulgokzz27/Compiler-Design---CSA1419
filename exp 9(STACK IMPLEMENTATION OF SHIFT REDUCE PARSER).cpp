#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
char temp[2], temp2[2];
char act[15];

void check();

int main() {
    printf("\n\t\tSHIFT REDUCE PARSER\n");
    printf("\nGRAMMAR");
    printf("\nE -> E+E");
    printf("\nE -> E/E");
    printf("\nE -> E*E");
    printf("\nE -> a/b");
    printf("\n\nEnter the input symbol: ");
    fgets(ip_sym, sizeof(ip_sym), stdin);
    ip_sym[strcspn(ip_sym, "\n")] = '\0'; 
    len = strlen(ip_sym);

    printf("\n\tStack Implementation Table");
    printf("\nStack\t\tInput Symbol\t\tAction");
    printf("\n$\t\t%s$\t\t--", ip_sym);

    strcpy(act, "shift ");
    temp[0] = ip_sym[ip_ptr];
    temp[1] = '\0';
    strcat(act, temp);

    for (i = 0; i < len; i++) {
        stack[st_ptr] = ip_sym[ip_ptr];
        stack[st_ptr + 1] = '\0';
        ip_sym[ip_ptr] = ' ';
        ip_ptr++;
        printf("\n$%s\t\t%s$\t\t%s", stack, ip_sym, act);

        strcpy(act, "shift ");
        temp[0] = ip_sym[ip_ptr];
        temp[1] = '\0';
        strcat(act, temp);
        check();
        st_ptr++;
    }
    st_ptr++;
    check();

    return 0;
}

void check() {
    char temp_stack[15];
    strcpy(temp_stack, stack);

    if (stack[st_ptr] == 'a' || stack[st_ptr] == 'b') {
        stack[st_ptr] = 'E';
        printf("\n$%s\t\t%s$\t\tE -> %c", stack, ip_sym, temp_stack[st_ptr]);
        return;
    }
    if (st_ptr >= 2 &&
        ((stack[st_ptr - 2] == 'E' && (stack[st_ptr - 1] == '+' || stack[st_ptr - 1] == '*' || stack[st_ptr - 1] == '/') && stack[st_ptr] == 'E'))) {
        stack[st_ptr - 2] = 'E';
        stack[st_ptr - 1] = '\0';
        stack[st_ptr] = '\0';
        st_ptr -= 2;

        printf("\n$%s\t\t%s$\t\tE -> E%cE", stack, ip_sym, temp_stack[st_ptr + 1]);
        return;
    }
    if (st_ptr == 0 && stack[0] == 'E' && ip_ptr == len) {
        printf("\n$%s\t\t%s$\t\tACCEPT", stack, ip_sym);
        exit(0);
    }
}

