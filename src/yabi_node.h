#ifndef YABI_NODE_H
#define YABI_NODE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct yabi_node {
        struct yabi_type *element;
        struct yabi_node *prev;
        struct yabi_node *next;
};

struct yabi_node_list {
        size_t length;
        struct yabi_node *head;
        struct yabi_node *tail;
};

/* node creation */
struct yabi_node *yabi_create_node(void);

/* list creation/deletion */
struct yabi_node_list *yabi_create_node_list(void);
void yabi_destroy_node_list(struct yabi_node_list *list);

/* node list functions */
bool yabi_node_list_is_empty(struct yabi_node_list *list);
struct yabi_node *yabi_node_list_peek(struct yabi_node_list *list);
struct yabi_node *yabi_node_list_pop(struct yabi_node_list *list);
void yabi_node_list_push(struct yabi_node_list *list, struct yabi_node *node);
void yabi_node_list_remove(struct yabi_node_list *list, struct yabi_node *node);
struct yabi_node_list *yabi_json_to_node_list(char *buffer);
struct yabi_node_list *yabi_bencode_to_node_list(char *buffer);
char *yabi_node_list_to_json(struct yabi_node_list *list);
char *yabi_json_to_bencode(char *buffer);

#endif /* YABI_NODE_H */
