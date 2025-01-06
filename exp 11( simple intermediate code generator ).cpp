#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct expression {
    char data[10], temp[7];
}s[30];

int main() {
    char d1[7], d2[7] = "t";
    int i = 0, j = 1, len = 0;
    FILE *f1, *f2;

    f1 = fopen("sum.txt", "r");
    if (f1 == NULL) {
        printf("Error: Unable to open file sum.txt\n");
        return 1;
    }

    f2 = fopen("out.txt", "w");
    if (f2 == NULL) {
        printf("Error: Unable to open file out.txt\n");
        fclose(f1);
        return 1;
    }

    // Reading input
    while (fscanf(f1, "%s", s[len].data) != EOF)
        len++;

    printf("Read tokens from input file:\n");
    for (i = 0; i < len; i++) {
        printf("%s\n", s[i].data);
    }

    // Processing
    itoa(j, d1, 10);
    strcat(d2, d1);
    strcpy(s[j].temp, d2);
    strcpy(d1, "");
    strcpy(d2, "t");

    fprintf(f2, "%s = %s + %s\n", s[j].temp, s[2].data, s[4].data);
    j++;

    for (i = 4; i < len - 2; i += 2) {
        itoa(j, d1, 10);
        strcat(d2, d1);
        strcpy(s[j].temp, d2);

        if (!strcmp(s[i + 1].data, "+"))
            fprintf(f2, "%s = %s + %s\n", s[j].temp, s[j - 1].temp, s[i + 2].data);
        else if (!strcmp(s[i + 1].data, "-"))
            fprintf(f2, "%s = %s - %s\n", s[j].temp, s[j - 1].temp, s[i + 2].data);

        strcpy(d1, "");
        strcpy(d2, "t");
        j++;
    }

    fprintf(f2, "%s = %s\n", s[0].data, s[j - 1].temp);

    fclose(f1);
    fclose(f2);

    printf("Output written to out.txt successfully.\n");
    return 0;
}

