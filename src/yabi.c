#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yabi.h"
#include "yabi_node.h"
#include "yabi_type.h"

int main(void)
{
        struct yabi_node_list *my_list = yabi_create_node_list();
        struct yabi_node *int_node = yabi_create_integer_node(55);
        struct yabi_node *str_node = yabi_create_string_node("Hewllo");

        yabi_node_list_append(my_list, int_node);
        yabi_node_list_append(my_list, str_node);

        printf("%zu\n", yabi_node_list_get_index(my_list, 0)->integer);

        // yabi_node_list_remove_node(my_list, int_node);

        struct yabi_type *last_elem = yabi_node_list_pop(my_list);

        printf("%zu\n", last_elem->integer);

        yabi_destroy_integer(last_elem);
        yabi_destroy_node_list(my_list);

        return EXIT_SUCCESS;
}
