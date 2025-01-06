#include <stdio.h>
#include <ctype.h>
#include <string.h> 

int main() {
    char a[10];
    int flag = 1, i = 1;

    printf("\nEnter an identifier: ");
    fgets(a, sizeof(a), stdin); 
    size_t len = strlen(a);
    if (len > 0 && a[len - 1] == '\n') {
        a[len - 1] = '\0';
    }

    if (!isalpha(a[0])) {
        printf("\nNot a valid identifier");
        return 0; 
    }

    while (a[i] != '\0') {
        if (!isalnum(a[i])) { 
            flag = 0;
            break;
        }
        i++;
    }

    if (flag == 1) {
        printf("\nValid identifier");
    } else {
        printf("\nNot a valid identifier");
    }

    return 0; 
}

