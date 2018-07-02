#include <stdlib.h>
#include <string.h>

#include "yabi_node.h"

static void empty_node_list(struct yabi_node_list *list);

struct yabi_node *yabi_create_node(struct yabi_type *element)
{
        struct yabi_node *ret = malloc(sizeof(struct yabi_node));

        if (ret == NULL) {
                return NULL;
        }

        ret->element = element;
        ret->prev = NULL;
        ret->next = NULL;

        return ret;
}

struct yabi_node_list *yabi_create_node_list(void)
{
        struct yabi_node_list *ret = malloc(sizeof(struct yabi_node_list));

        if (ret == NULL) {
                return NULL;
        }

        ret->length = 0;
        ret->head = NULL;
        ret->tail = NULL;

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
        if (yabi_node_list_is_empty(list)) {
                return;
        }

        struct yabi_node *head = list->head;
        struct yabi_node *tmp;

        while (head != NULL) {
                /*
                 * Since we are clearing the entire node list there is no point
                 * in using yabi_destroy_node as keeping the tree together is
                 * not needed
                 */
                tmp = head;
                head = head->prev;

                yabi_destroy_element(tmp->element);
                free(tmp);
        }

        list->length = 0;
        list->head = NULL;
        list->tail = NULL;
}

bool yabi_node_list_is_empty(struct yabi_node_list *list)
{
        return list->length == 0;
}

struct yabi_node *yabi_node_list_peek(struct yabi_node_list *list)
{
        return list->head;
}

struct yabi_type *yabi_node_list_pop(struct yabi_node_list *list)
{
        if (yabi_node_list_is_empty(list)) {
                return NULL;
        }

        /* TODO: Fix this */
        return NULL;
}

void yabi_node_list_push(struct yabi_node_list *list, struct yabi_type *element)
{
        struct yabi_node *node = yabi_create_node(element);

        if (yabi_node_list_is_empty(list)) {
                list->head = node;
                ++list->length;
        } else {
                list->head->next = node;
                node->prev = list->head;
                list->head = node;
                ++list->length;
        }
}

void yabi_node_list_remove(struct yabi_node_list *list, struct yabi_node *node)
{
        /* don't leave a gap in the list */
        if (node->prev != NULL) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
        } else {
                list->head = node->next;
                list->tail = node->prev;
        }

        free(node);
}
