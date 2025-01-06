#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int size = 0;
struct SymbTab *first = NULL, *last = NULL;

typedef struct SymbTab {
    char label[10];
    char symbol[10];
    int addr;
    struct SymbTab *next;
} SymbTab;

void Insert();
void Display();
void Delete();
int Search(char lab[]);
void Modify();

int main() {
    int op, y;
    char la[10];
    do {
        printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
        printf("\n\t1.INSERT\n\t2.DISPLAY\n\t3.DELETE\n\t4.SEARCH\n\t5.MODIFY\n\t6.END\n");
        printf("\n\tEnter your option: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                Insert();
                break;
            case 2:
                Display();
                break;
            case 3:
                Delete();
                break;
            case 4:
                printf("\n\tEnter the label to be searched: ");
                scanf("%s", la);
                y = Search(la);
                if (y == 1)
                    printf("\n\tThe label is present in the symbol table.\n");
                else
                    printf("\n\tThe label is not present in the symbol table.\n");
                break;
            case 5:
                Modify();
                break;
            case 6:
                printf("\n\tExiting...\n");
                exit(0);
            default:
                printf("\n\tInvalid option! Please try again.\n");
        }
    } while (op != 6);
    return 0;
}

void Insert() {
    int n;
    char l[10];
    printf("\n\tEnter the label: ");
    scanf("%s", l);
    n = Search(l);
    if (n == 1) {
        printf("\n\tThe label exists already in the symbol table. Duplicate can't be inserted.\n");
    } else {
        struct SymbTab *p = (struct SymbTab *)malloc(sizeof(struct SymbTab));
        strcpy(p->label, l);
        printf("\n\tEnter the symbol: ");
        scanf("%s", p->symbol);
        printf("\n\tEnter the address: ");
        scanf("%d", &p->addr);
        p->next = NULL;

        if (size == 0) {
            first = p;
            last = p;
        } else {
            last->next = p;
            last = p;
        }
        size++;
        printf("\n\tLabel inserted.\n");
    }
}

void Display() {
    struct SymbTab *p = first;
    if (size == 0) {
        printf("\n\tSymbol table is empty.\n");
        return;
    }
    printf("\n\tLABEL\t\tSYMBOL\t\tADDRESS\n");
    while (p != NULL) {
        printf("\t%s\t\t%s\t\t%d\n", p->label, p->symbol, p->addr);
        p = p->next;
    }
}

int Search(char lab[]) {
    struct SymbTab *p = first;
    while (p != NULL) {
        if (strcmp(p->label, lab) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

void Modify() {
    char l[10], nl[10];
    int add, choice;
    struct SymbTab *p = first;

    printf("\n\tWhat do you want to modify?\n");
    printf("\t1. Only the label\n");
    printf("\t2. Only the address\n");
    printf("\t3. Both the label and address\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\n\tEnter the old label: ");
            scanf("%s", l);
            if (!Search(l)) {
                printf("\n\tLabel not found.\n");
            } else {
                printf("\n\tEnter the new label: ");
                scanf("%s", nl);
                while (p != NULL) {
                    if (strcmp(p->label, l) == 0) {
                        strcpy(p->label, nl);
                        break;
                    }
                    p = p->next;
                }
                printf("\n\tAfter modification:\n");
                Display();
            }
            break;
        case 2:
            printf("\n\tEnter the label whose address is to be modified: ");
            scanf("%s", l);
            if (!Search(l)) {
                printf("\n\tLabel not found.\n");
            } else {
                printf("\n\tEnter the new address: ");
                scanf("%d", &add);
                while (p != NULL) {
                    if (strcmp(p->label, l) == 0) {
                        p->addr = add;
                        break;
                    }
                    p = p->next;
                }
                printf("\n\tAfter modification:\n");
                Display();
            }
            break;
        case 3:
            printf("\n\tEnter the old label: ");
            scanf("%s", l);
            if (!Search(l)) {
                printf("\n\tLabel not found.\n");
            } else {
                printf("\n\tEnter the new label: ");
                scanf("%s", nl);
                printf("\n\tEnter the new address: ");
                scanf("%d", &add);
                while (p != NULL) {
                    if (strcmp(p->label, l) == 0) {
                        strcpy(p->label, nl);
                        p->addr = add;
                        break;
                    }
                    p = p->next;
                }
                printf("\n\tAfter modification:\n");
                Display();
            }
            break;
        default:
            printf("\n\tInvalid choice!\n");
    }
}

void Delete() {
    char l[10];
    struct SymbTab *p = first, *q = NULL;

    printf("\n\tEnter the label to be deleted: ");
    scanf("%s", l);

    if (!Search(l)) {
        printf("\n\tLabel not found.\n");
        return;
    }

    if (strcmp(first->label, l) == 0) {
        first = first->next;
    } else {
        while (p != NULL && strcmp(p->label, l) != 0) {
            q = p;
            p = p->next;
        }
        if (p == last) {
            last = q;
        }
        if (q != NULL) {
            q->next = p->next;
        }
    }
    free(p);
    size--;
    printf("\n\tLabel deleted.\n");
    printf("\n\tAfter deletion:\n");
    Display();
}

