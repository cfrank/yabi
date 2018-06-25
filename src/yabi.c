#include <stdio.h>
#include <stdlib.h>

#include "yabi.h"

static void empty_node_list(struct yabi_node_list *list);

struct yabi_node_list *yabi_create_node_list(void)
{
        struct yabi_node_list *ret = malloc(sizeof(struct yabi_node_list));

        if (ret == NULL) {
                return NULL;
        }

        ret->length = 0;
        ret->head = NULL;

        return ret;
}

void yabi_destroy_node_list(struct yabi_node_list *list)
{
        /* Loop through the list and destroy all the nodes */
        empty_node_list(list);

        free(list);
}

static void empty_node_list(struct yabi_node_list *list)
{
        struct yabi_node *current_node = list->head;
        struct yabi_node *next_node = current_node->next;

        while (current_node != NULL) {
                /*
                 * Since we are clearing the entire node list there is no point
                 * in using yabi_destroy_node as keeping the tree together is
                 * not needed
                 */
                free(current_node);

                current_node = next_node;
                next_node = current_node->next;
        }

        list->length = 0;
        list->head = NULL;
        list->tail = NULL;
}

struct yabi_node *yabi_create_node(void)
{
        struct yabi_node *ret = malloc(sizeof(struct yabi_node));

        if (ret == NULL) {
                return NULL;
        }

        ret->element = NULL;
        ret->prev = NULL;
        ret->next = NULL;

        return ret;
}

void yabi_destroy_node(struct yabi_node_list *list, struct yabi_node *node)
{
        /* don't leave a gap in the list */
        if (node->prev != NULL) {
                node->prev->next = node->next;
        } else {
                list->head = node->next;
        }

        if (node->next != NULL) {
                node->next->prev = node->prev;
        } else {
                list->tail = node->prev;
        }

        free(node);
}

struct yabi_node *yabi_node_list_peek(struct yabi_node_list *list)
{
        return list->head;
}

int main(void)
{
        printf("%s", "Hello world");

        return EXIT_SUCCESS;
}
