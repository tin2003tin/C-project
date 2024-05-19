#include <stdio.h>
#include <string.h>
#include "global/data_structure/AVL_orderMap/AVL_orderMap.h"
#include "global/data_structure/utilities/func.h"

struct User
{
    char *firstName;
    int age;
    int id;
    char *lastName;
};

struct User create_user(int id, char *firstName, char *lastName, int age)
{
    struct User user;
    user.id = id;
    user.firstName = firstName;
    user.lastName = lastName;
    user.age = age;
    return user;
}

void user_display(const void *element)
{
    struct User *user = (struct User *)element;
    printf("{ Id: %d", user->id);
    printf(", FirstName: %s", user->firstName);
    printf(", LastName: %s", user->lastName);
    printf(", Age: %d }", user->age);
}

int main()
{
    T_AVL_OrderMap map = t_AVL_ordermap_init(sizeof(int), sizeof(struct User), t_utilities_compareInt, t_utilities_equalInt);
    for (int i = 1; i <= 100; i += i + 1)
    {
        char firstName[20];
        char lastName[20];
        sprintf(firstName, "User%d", i);
        sprintf(lastName, "Last%d", i);
        struct User newUser = create_user(i, firstName, lastName, 20 + i);
        t_AVL_ordermap_insert(&map, &newUser.id, &newUser);
    }
    t_AVL_ordermap_displayBreadth(&map, t_utilities_display_int, user_display);
    int key = 63;
    struct User *user = t_AVL_ordermap_find(&map, &key);
    if (user == NULL)
    {
        printf("user is not found");
        return 1;
    }
    user_display(user);
    printf("\n");
    t_AVL_ordermap_destroy(&map);
}