#ifndef YABI_LIST_H
#define YABI_LIST_H

#include <stdbool.h>
#include <stdint.h>

#include "yabi_type.h"

struct yabi_node {
        struct yabi_type *element;
        struct yabi_node *next;
};

struct yabi_node_list {
        size_t length;
        struct yabi_node *head;
        struct yabi_node *tail;
};

/* Node list creation/deletion */
struct yabi_node_list *yabi_create_node_list(void);
void yabi_destroy_node_list(struct yabi_node_list *list);

/* Node creation/deletion */
struct yabi_node *yabi_create_node(struct yabi_type *element);
struct yabi_node *yabi_create_string_node(const char *string);
struct yabi_node *yabi_create_integer_node(size_t integer);
struct yabi_node *yabi_create_list_node(struct yabi_type **list, size_t length);
struct yabi_node *
yabi_create_dictionary_node(struct yabi_dictionary_element **dictionary,
                            size_t length);
void yabi_destroy_node(struct yabi_node *node);

/* List helpers */
bool yabi_node_list_is_empty(struct yabi_node_list *list);

/* Getters */
struct yabi_type *yabi_node_list_get_head(struct yabi_node_list *list);
struct yabi_type *yabi_node_list_get_tail(struct yabi_node_list *list);
struct yabi_type *yabi_node_list_get_index(struct yabi_node_list *list,
                                           size_t index);

/* Insertion/removal */
void yabi_node_list_append(struct yabi_node_list *list, struct yabi_node *node);
bool yabi_node_list_append_after(struct yabi_node_list *list,
                                 struct yabi_node *after,
                                 struct yabi_node *node);
void yabi_node_list_prepend(struct yabi_node_list *list,
                            struct yabi_node *node);
struct yabi_type *yabi_node_list_peek(struct yabi_node_list *list);
struct yabi_type *yabi_node_list_pop(struct yabi_node_list *list);
void yabi_node_list_remove_node(struct yabi_node_list *list,
                                struct yabi_node *node);

#endif /* YABI_LIST_H */
