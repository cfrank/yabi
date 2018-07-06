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
        struct yabi_node *string_node
                = yabi_create_string_node("Hello node str");

        yabi_node_list_append(my_list, int_node);
        yabi_node_list_append(my_list, string_node);

        printf("%s\n", "Hello world");

        printf("%zu\n", yabi_node_list_get_index(my_list, 0)->integer);
        printf("%s\n", yabi_node_list_get_index(my_list, 1)->string->value);

        yabi_destroy_node_list(my_list);

        return EXIT_SUCCESS;
}
