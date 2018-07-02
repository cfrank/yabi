#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yabi.h"
#include "yabi_node.h"
#include "yabi_type.h"

int main(void)
{
        struct yabi_node_list *list = yabi_create_node_list();
        struct yabi_type *my_string = yabi_create_string("Hello world");
        struct yabi_type *my_int = yabi_create_integer(55);

        printf("%zu\n", yabi_get_integer(my_int));

        yabi_node_list_push(list, my_string);
        yabi_node_list_push(list, my_int);

        yabi_destroy_node_list(list);

        return EXIT_SUCCESS;
}
