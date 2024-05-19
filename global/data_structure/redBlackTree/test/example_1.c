#include <stdio.h>
#include "global/data_structure/redBlackTree/redBlackTree.h"

int main()
{
    T_RedBlack_Tree tree = t_redblack_tree_init(sizeof(int), sizeof(int), t_utilities_compareInt, t_utilities_equalInt);
    int id[8] = {42, 10, 64, 7, 29, 50, 83, 31};

    for (size_t i = 0; i < sizeof(id) / sizeof(id[0]); i++)
    {
        t_redblack_tree_insert(&tree, &id[i], &id[i]);
    }

    t_redblack_displayBreadth(&tree, t_utilities_display_int, t_utilities_display_int);

    int delete_id = 10;

    t_redblack_tree_remove(&tree, &delete_id);

    delete_id = 31;

    t_redblack_tree_remove(&tree, &delete_id);
    delete_id = 7;

    t_redblack_tree_remove(&tree, &delete_id);
    delete_id = 29;

    t_redblack_tree_remove(&tree, &delete_id);
    printf("\n\n");
    t_redblack_displayBreadth(&tree, t_utilities_display_int, t_utilities_display_int);

    t_redblack_tree_destroy(&tree);
    return 0;
}