#include <stdio.h>
#include <stdlib.h>

#include "yabi_node.h"
#include "yabi_type.h"

static void empty_node_list(struct yabi_node_list *list);
static void destroy_node(struct yabi_node *node);

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

static void empty_node_list(struct yabi_node_list *list)
{
        if (yabi_node_list_is_empty(list)) {
                return;
        }

        struct yabi_node *current_node = list->head;

        while (list->head != NULL) {
                current_node = list->head;
                list->head = current_node->next;
                --list->length;

                yabi_destroy_node(current_node);
        }
}

void yabi_destroy_node_list(struct yabi_node_list *list)
{
        empty_node_list(list);

        free(list);
}

struct yabi_node *yabi_create_node(struct yabi_type *element)
{
        struct yabi_node *ret = malloc(sizeof(struct yabi_node));

        if (ret == NULL) {
                return NULL;
        }

        ret->element = element;
        ret->next = NULL;

        return ret;
}

static void destroy_node(struct yabi_node *node)
{
        free(node);
}

struct yabi_node *yabi_create_string_node(const char *string)
{
        return yabi_create_node(yabi_create_string(string));
}

struct yabi_node *yabi_create_integer_node(size_t integer)
{
        return yabi_create_node(yabi_create_integer(integer));
}

struct yabi_node *yabi_create_list_node(struct yabi_type **list, size_t length)
{
        return yabi_create_node(yabi_create_list(list, length));
}

struct yabi_node *
yabi_create_dictionary_node(struct yabi_dictionary_element **dictionary,
                            size_t length)
{
        return yabi_create_node(yabi_create_dictionary(dictionary, length));
}

void yabi_destroy_node(struct yabi_node *node)
{
        yabi_destroy_element(node->element);

        free(node);
}

bool yabi_node_list_is_empty(struct yabi_node_list *list)
{
        return list->length == 0;
}

struct yabi_type *yabi_node_list_get_head(struct yabi_node_list *list)
{
        return list->head->element;
}

struct yabi_type *yabi_node_list_get_tail(struct yabi_node_list *list)
{
        return list->tail->element;
}

struct yabi_type *yabi_node_list_get_index(struct yabi_node_list *list,
                                           size_t index)
{
        if (index > list->length) {
                return NULL;
        }

        struct yabi_node *current_node = list->head;

        for (size_t i = 0; i < index; ++i) {
                current_node = current_node->next;
        }

        return current_node->element;
}

void yabi_node_list_append(struct yabi_node_list *list, struct yabi_node *node)
{
        if (yabi_node_list_is_empty(list)) {
                list->head = node;
                list->tail = node;
        } else {
                struct yabi_node *current_node = list->head;
                while (current_node->next != NULL) {
                        current_node = current_node->next;
                }

                current_node->next = node;
                list->tail = node;
        }

        ++list->length;
}

bool yabi_node_list_append_after(struct yabi_node_list *list,
                                 struct yabi_node *after,
                                 struct yabi_node *node)
{
        struct yabi_node *current_node = list->head;

        while (current_node != NULL) {
                /* Both pointers must point to the same address */
                if (after == current_node) {
                        /* Insert here */
                        node->next = current_node->next;
                        current_node->next = node;
                        ++list->length;
                        return true;
                } else {
                        current_node = current_node->next;
                }
        }

        return false;
}

void yabi_node_list_prepend(struct yabi_node_list *list, struct yabi_node *node)
{
        if (yabi_node_list_is_empty(list)) {
                list->head = node;
                list->tail = node;
        } else {
                node->next = list->tail;
                list->tail = node;
        }

        ++list->length;
}

struct yabi_type *yabi_node_list_peek(struct yabi_node_list *list)
{
        if (yabi_node_list_is_empty(list)) {
                return NULL;
        }

        return list->head->element;
}

struct yabi_type *yabi_node_list_pop(struct yabi_node_list *list)
{
        if (yabi_node_list_is_empty(list)) {
                return NULL;
        }

        struct yabi_node *head = list->head;
        struct yabi_type *ret = list->head->element;

        list->head = list->head->next;

        destroy_node(head);

        return ret;
}

void yabi_node_list_remove_node(struct yabi_node_list *list,
                                struct yabi_node *node)
{
        if (yabi_node_list_is_empty(list)) {
                return;
        }

        if (node->next != NULL) {
                struct yabi_node *tmp = node->next;
                node->element = tmp->element;
                node->next = tmp->next;

                yabi_destroy_node(tmp);
        } else {
                struct yabi_node *current_node = list->head;
                struct yabi_node *prev = list->head;

                while (prev->next != NULL) {
                        prev = current_node;
                        current_node = current_node->next;
                }

                yabi_destroy_node(current_node);
                prev->next = NULL;
                list->tail = prev;
        }

        --list->length;
}
