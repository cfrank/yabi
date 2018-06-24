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
        ENOMEM, /* Allocation failed */
        ELOOP, /* Recursion limit reached */
        EBADFMT, /* Encountered bad format */
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

struct yabi_list {
        size_t length;
        struct yabi_node *head;
};

/* list creation/deletion */
struct yabi_node *create_list(void);
void destroy_list(struct yabi_node *list);

/* read in elements */
yabi_string *read_yabi_string(char *buffer);
size_t read_yabi_integer(char *buffer);
struct yabi_type **read_yabi_list(char *buffer);
struct yabi_dictionary **read_yabi_dictionary(char *buffer);

#endif /* YABI_H */
