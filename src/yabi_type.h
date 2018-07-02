#ifndef YABI_TYPE_H
#define YABI_TYPE_H

#include <stdint.h>
#include <stdio.h>

enum yabi_element {
        YABI_STRING,
        YABI_INTEGER,
        YABI_LIST,
        YABI_DICTIONARY,
};

struct yabi_dictionary_element {
        const char *key;
        struct yabi_type *value;
};

struct yabi_string {
        size_t size;
        const char *value;
};

struct yabi_list {
        size_t length;
        struct yabi_type **list_items;
};

struct yabi_dictionary {
        size_t length;
        struct yabi_dictionary_element **dictionary_items;
};

struct yabi_type {
        enum yabi_element type;
        union {
                struct yabi_string *string;
                size_t integer;
                struct yabi_list *list;
                struct yabi_dictionary *dictionary;
        };
};

/* element creating/deletion */
void yabi_destroy_element(struct yabi_type *element);
struct yabi_type *yabi_create_string(const char *string);
struct yabi_string *yabi_get_string(struct yabi_type *element);
void yabi_destroy_string(struct yabi_type *element);
struct yabi_type *yabi_create_integer(size_t integer);
size_t yabi_get_integer(struct yabi_type *element);
void yabi_destroy_integer(struct yabi_type *element);
struct yabi_type *yabi_create_list(struct yabi_type **list, size_t length);
void yabi_destroy_list(struct yabi_type *element);
struct yabi_dictionary_element *
yabi_create_dictionary_element(const char *key, struct yabi_type *value);
void yabi_destroy_dictionary_element(struct yabi_dictionary_element *element);
void yabi_destroy_dictionary(struct yabi_type *element);

#endif /* YABI_TYPE_H */
