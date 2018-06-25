#ifndef YABI_H
#define YABI_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum yabi_element {
        YABI_STRING,
        YABI_INTEGER,
        YABI_LIST,
        YABI_DICTIONARY,
};

enum yabi_err {
        ESUCCESS = 0, /* No error */
        ENOMEM = -1, /* Allocation failed */
        ELOOP = -2, /* Recursion limit reached */
        EBADFMT = -3, /* Encountered bad format */
};

struct yabi_dictionary_element {
        const char *key;
        struct yabi_type *value;
};

struct yabi_string {
        size_t size;
        const char *value;
};

struct yabi_type {
        enum yabi_element type;
        union {
                struct yabi_string *string;
                size_t integer;
                struct yabi_type **list;
                struct yabi_dictionary_element **dictionary;
        };
};

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

/* list creation/deletion */
struct yabi_node_list *yabi_create_node_list(void);
void yabi_destroy_node_list(struct yabi_node_list *list);

/* node list functions */
struct yabi_node *yabi_node_list_peek(struct yabi_node_list *list);
struct yabi_node *yabi_node_list_pop(struct yabi_node_list *list);
enum yabi_err yabi_node_list_push(struct yabi_node_list *list);
struct yabi_node_list *yabi_json_to_node_list(char *buffer);
struct yabi_node_list *yabi_bencode_to_node_list(char *buffer);
char *yabi_node_list_to_json(struct yabi_node_list *list);
char *yabi_json_to_bencode(char *buffer);

/* node creation/deletion */
struct yabi_node *yabi_create_node(void);
void yabi_destroy_node(struct yabi_node_list *list, struct yabi_node *node);

/* element creating/deletion */
struct yabi_type *yabi_create_string(void);
void yabi_destroy_string(struct yabi_string *element);
struct yabi_type *yabi_create_dictionary_element(void);
void yabi_destroy_dictionary_element(struct yabi_dictionary_element *element);

/* read in elements */
struct yabi_type *yabi_read_string(char *buffer);
struct yabi_type *yabi_read_integer(char *buffer);
struct yabi_type *yabi_read_list(char *buffer);
struct yabi_type *yabi_read_dictionary_element(char *buffer);

/* output elements */
char *yabi_output_string(struct yabi_type *element);
char *yabi_output_integer(struct yabi_type *element);
char *yabi_output_list(struct yabi_type *element);
char *yabi_output_dictionary_element(struct yabi_type *element);

#endif /* YABI_H */
