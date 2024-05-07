#include <stdio.h>
#include <stdlib.h>
typedef struct Book Book;

struct Book
{
    int id;
    char *name;
};

int main()
{
    Book *book = malloc(sizeof(Book));

    return 0;
}