#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../pqueue.h"

typedef struct Book
{
    int id;
    char *name;
    char *author;
    int price;
    bool isPublished;
} Book;

Book book_create(int id, const char *name, const char *author, int price, bool isPublished)
{
    Book book;
    book.id = id;
    book.name = strdup(name);
    book.author = strdup(author);
    book.price = price;
    book.isPublished = isPublished;
    return book;
}

void book_destroy(Book *book)
{
    free(book->name);
    free(book->author);
}

const void book_display(const void *element)
{
    Book *book = (Book *)element;
    printf("--%s--\n", book->name);
    printf("Id: %d\n", book->id);
    printf("Author: %s\n", book->author);
    printf("Price: %d\n", book->price);
    printf("isPublished: %d\n", book->isPublished);
    printf("\n");
}

bool book_compare(const void *book1, const void *book2)
{
    return (*(Book *)book1).price > (*(Book *)book2).price;
}
int main()
{
    Book book1 = book_create(1, "Fairy Tail", "Tin", 200, true);
    Book book2 = book_create(2, "Waterfall", "Job", 300, false);
    Book book3 = book_create(3, "Gramble Guide", "Mark", 500, true);
    Book book4 = book_create(4, "Gaming Gear", "Nut", 1000, false);
    Book book5 = book_create(5, "Coconut", "Monkey", 299, true);
    Book book6 = book_create(6, "Cheapest", "Me", 50, true);
    Book book7 = book_create(7, "Expensive", "Who", 50000, true);

    T_PQueue pqueue = t_Pqueue_init(sizeof(Book), book_compare);

    t_Pqueue_enqueue(&pqueue, &book1);
    t_Pqueue_enqueue(&pqueue, &book2);
    t_Pqueue_enqueue(&pqueue, &book3);
    t_Pqueue_enqueue(&pqueue, &book4);
    t_Pqueue_enqueue(&pqueue, &book5);

    t_Pqueue_display(&pqueue, book_display);
    printf("============= Front\n");
    printf("size: %d\n", t_Pqueue_get_size(&pqueue));
    printf("cap: %d\n", t_Pqueue_get_capacity(&pqueue));
    printf("typeSize: %d\n", t_Pqueue_get_typeSize(&pqueue));
    printf("\n");

    book_display(t_Pqueue_front(&pqueue));

    printf("============= After Dequeue\n");
    t_Pqueue_dequeue(&pqueue);
    t_Pqueue_dequeue(&pqueue);
    t_Pqueue_dequeue(&pqueue);
    t_Pqueue_enqueue(&pqueue, &book7);
    t_Pqueue_enqueue(&pqueue, &book6);
    t_Pqueue_dequeue(&pqueue);
    t_Pqueue_dequeue(&pqueue);
    t_Pqueue_dequeue(&pqueue);
    // t_Pqueue_dequeue(&pqueue);

    printf("size: %d\n", t_Pqueue_get_size(&pqueue));
    printf("cap: %d\n", t_Pqueue_get_capacity(&pqueue));
    printf("typeSize: %d\n", t_Pqueue_get_typeSize(&pqueue));
    printf("\n");
    // t_Pqueue_display(&pqueue, book_display);
    book_display(t_Pqueue_front(&pqueue));

    return 0;
}
