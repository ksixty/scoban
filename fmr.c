#include <stdio.h>
#include <stdlib.h>
#define HNULL NULL

struct Cell 
{
    int value;
    struct Cell* next;
};

struct Cell* list(int values[], size_t valuesc)
{
    size_t count = valuesc / sizeof(int) - 1;
    struct Cell* first = malloc(sizeof(struct Cell));
    struct Cell* temp = first;

    for (int i = 0; i < count; i++) {
        temp->value = values[i]; 
        temp->next = malloc(sizeof(struct Cell));
        temp = temp->next;
    }

    temp->value = values[count]; 
    temp->next = HNULL;

    return first;
}

int car(struct Cell* list)
{
    return list->value;
}

struct Cell* cdr(struct Cell* list)
{
    return list->next;     
}

void printlval(struct Cell* list)
{
    printf("%d", car(list));
    if (cdr(list) != HNULL) {
        printf(" ");
        printlval(cdr(list));
    }
}

void printl(struct Cell* list)
{
    printf("(");
    if (cdr(list) != HNULL)
        printlval(cdr(list));
    printf(")");
}

int main(int argc, char* argv[])
{
    int a[] = {0, 1, 2, 3, 4, 5, 6};
    struct Cell* al = list(a, sizeof(a));
    printl(al);
    return 0;
}
