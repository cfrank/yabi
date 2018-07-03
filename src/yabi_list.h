#ifndef YABI_LIST_H
#define YABI_LIST_H

#include <stdbool.h>
#include <stdint.h>

#include "yabi_type.h"

struct yabi_list_node {
        struct yabi_type *element;
        struct yabi_node *next;
};

struct yabi_list {
        size_t length;
        struct yabi_list_node *head;
        struct yabi_list_node *tail;
};

/* List creation/deletion */
struct yabi_list *yabi_create_list(void);
void yabi_destroy_list(struct yabi_list *list);

/* Node creation/deletion */
struct yabi_list_node *yabi_create_list_node(struct yabi_type *element);
void yabi_destroy_list_node(struct yabi_list_node *node);

/* List helpers */
bool yabi_list_is_empty(struct yabi_list *list);

/* Insertion/removal */
void yabi_list_append(struct yabi_list *list, struct yabi_list_node *node);
bool yabi_list_append_after(struct yabi_list *list,
                            struct yabi_list_node *after,
                            struct yabi_list_node *node);
void yabi_list_prepend(struct yabi_list *list, struct yabi_list_node *node);
struct yabi_type *yabi_list_peek(struct yabi_list *list);
struct yabi_type *yabi_list_pop(struct yabi_list *list);
void yabi_list_remove_node(struct yabi_list *list, struct yabi_list_node *node);

/* Getters */
struct yabi_type *yabi_get_tail(struct yabi_list *list);
struct yabi_type *yabi_get_index(struct yabi_list *list, size_t index);

#endif /* YABI_LIST_H */
