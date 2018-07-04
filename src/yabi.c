#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yabi.h"
#include "yabi_node.h"
#include "yabi_type.h"

int main(void)
{
        struct yabi_node_list *my_list = yabi_create_node_list();
        struct yabi_type *my_string = yabi_create_string("Hello from string");
        struct yabi_node *string_node = yabi_create_node(my_string);

        yabi_node_list_append(my_list, string_node);

        printf("%s\n", "Hello world");

        printf("%s\n", yabi_node_list_get_index(my_list, 0)->string->value);

        yabi_destroy_node_list(my_list);

        return EXIT_SUCCESS;
}
