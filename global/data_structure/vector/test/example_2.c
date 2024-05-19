#include <stdio.h>
#include <stdbool.h>

#include "global/data_structure/vector/vector.h"

typedef struct Book
{
    char *name;
    char *author;
    int price;
    bool isPublished;
} Book;

Book book_create(char *name, char *author, int price, bool isPublished)
{
    Book book;
    book.name = name;
    book.author = author;
    book.price = price;
    book.isPublished = isPublished;
    return book;
}

const void book_display(const void *element)
{
    Book *book = (Book *)element;
    printf("--%s--\n", book->name);
    printf("Author: %s\n", book->author);
    printf("Price: %d\n", book->price);
    printf("isPublished: %d\n", book->isPublished);
}

int main()
{
    Book book1 = book_create("Fairy Tail", "Tin", 200, true);
    Book book2 = book_create("Waterfall", "Job", 100, false);
    Book book3 = book_create("Gramble Guide", "Mark", 500, true);

    T_Vector vector = T_VECTOR_NEW(Book);
    t_vector_push_back(&vector, &book1);
    t_vector_push_back(&vector, &book2);
    t_vector_push_back(&vector, &book3);
    t_vector_display(&vector, book_display);

    // for (int index = 0; index < t_vector_get_size(&vector); index++)
    // {
    //     book_display(&(T_VECTOR_GET_VALUE_AS(Book, &vector, index)));
    //     printf("\n");
    // }

    t_vector_destroy(&vector);
    return 0;
}