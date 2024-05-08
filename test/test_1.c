#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

void book_display(const Book *book)
{
    printf("--%s--\n", book->name);
    printf("Id: %d\n", book->id);
    printf("Author: %s\n", book->author);
    printf("Price: %d\n", book->price);
    printf("isPublished: %d\n", book->isPublished);
}

bool book_id_greater(const void *book1, const void *book2)
{
    return (*(Book *)book1).id > (*(Book *)book2).id;
}
bool book_price_greater(const void *book1, const void *book2)
{
    return (*(Book *)book1).price > (*(Book *)book2).price;
}

const void *min(const void *x, const void *y, bool (*compareFunc)(const void *, const void *))
{
    return compareFunc(x, y) ? y : x;
}

int main()
{
    Book book1 = book_create(1, "Fairy Tail", "Tin", 200, true);
    Book book2 = book_create(2, "Waterfall", "Job", 100, false);
    Book book3 = book_create(3, "Gramble Guide", "Mark", 500, true);
    const Book *maxIdBook = min(&book1, &book2, book_id_greater);
    const Book *maxPriceBook = min(&book1, &book2, book_price_greater);
    printf("Min Id book\n");
    book_display(maxIdBook);
    printf("\nMin Price book\n");
    book_display(maxPriceBook);

    // Free memory allocated for the books
    book_destroy(&book1);
    book_destroy(&book2);
    book_destroy(&book3);

    return 0;
}
