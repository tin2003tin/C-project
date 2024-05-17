#include <stdio.h>
#include <stdbool.h>

#include "global/hashMap/hashmap.h"
#include "global/utilities/hash.h"
#include "global/utilities/func.h"

struct Product
{
    int id;
    char *name;
    char *timeStemp;
    size_t price;
};

struct Product createProduct(int id, char *name, char *timeStemp, size_t price)
{
    struct Product product;
    product.id = id;
    product.name = name;
    product.price = price;
    product.timeStemp = timeStemp;
    return product;
}

const void displayProduct(const void *element)
{
    struct Product *product = (struct Product *)element;
    printf("---%d---\n", product->id);
    printf("name: %s\n", product->name);
    printf("timeStemp: %s\n", product->timeStemp);
    printf("price: %d\n", product->price);
}

int main()
{
    T_HashMap hashmap = t_hashmap_init(sizeof(int), sizeof(struct Product), t_utilities_hash_int, t_utilities_equalInt);
    struct Product shampoo = createProduct(101, "Shampoo", "16/05/2567", 299);
    struct Product toothpaste = createProduct(103, "Tootpaste", "15/05/2567", 199);
    t_hashmap_put(&hashmap, &shampoo.id, &shampoo);
    t_hashmap_put(&hashmap, &toothpaste.id, &toothpaste);
    for (int i = 0; i < hashmap.bucketsLength; i++)
    {
        printf("Bucket: %d\n", i);
        for (int j = 0; j < hashmap.buckets[i].vector.size; j++)
        {
            T_Pair pair = T_VECTOR_GET_VALUE_AS(T_Pair, &hashmap.buckets[i].vector, j);
            displayProduct(pair.second);
        }
    }
    return 0;
}