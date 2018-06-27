#include <stdlib.h>
#include <string.h>

#include "yabi_type.h"

static struct yabi_type *create_yabi_type(void)
{
        struct yabi_type *ret = malloc(sizeof(struct yabi_type));

        if (ret == NULL) {
                return NULL;
        }

        return ret;
}

void yabi_destroy_element(struct yabi_type *element)
{
        switch (element->type) {
        case YABI_DICTIONARY:
                yabi_destroy_dictionary(element);
                break;
        case YABI_INTEGER:
                yabi_destroy_integer(element);
                break;
        case YABI_LIST:
                yabi_destroy_list(element);
                break;
        case YABI_STRING:
                yabi_destroy_string(element);
                break;
        }
}

struct yabi_type *yabi_create_string(const char *string)
{
        struct yabi_type *ret = create_yabi_type();
        struct yabi_string *string_data = malloc(sizeof(struct yabi_string));

        if (ret == NULL || string_data == NULL) {
                return NULL;
        }

        string_data->size = strlen(string) + 1;
        string_data->value = string;

        ret->type = YABI_STRING;
        ret->string = string_data;

        return ret;
}

void yabi_destroy_string(struct yabi_type *element)
{
        free(element->string);
        free(element);
}

struct yabi_type *yabi_create_integer(size_t integer)
{
        struct yabi_type *ret = create_yabi_type();

        if (ret == NULL) {
                return NULL;
        }

        ret->type = YABI_INTEGER;
        ret->integer = integer;

        return ret;
}

void yabi_destroy_integer(struct yabi_type *element)
{
        free(element);
}

struct yabi_type *yabi_create_list(struct yabi_type **list, size_t length)
{
        struct yabi_type *ret = create_yabi_type();
        struct yabi_list *list_data = malloc(sizeof(struct yabi_list));

        if (ret == NULL || list_data == NULL) {
                return NULL;
        }

        list_data->length = length;
        list_data->list_items = list;

        ret->type = YABI_LIST;
        ret->list = list_data;

        return ret;
}

void yabi_destroy_list(struct yabi_type *element)
{
        for (size_t i = 0; i < element->list->length; ++i) {
                yabi_destroy_element(element->list->list_items[i]);
        }

        free(element->list);
        free(element);
}

struct yabi_dictionary_element *
yabi_create_dictionary_element(const char *key, struct yabi_type *value)
{
        struct yabi_dictionary_element *ret
                = malloc(sizeof(struct yabi_dictionary_element));

        if (ret == NULL) {
                return NULL;
        }

        ret->key = key;
        ret->value = value;

        return ret;
}

struct yabi_type *
yabi_create_dictionary(struct yabi_dictionary_element **dictionary,
                       size_t length)
{
        struct yabi_type *ret = create_yabi_type();
        struct yabi_dictionary *dictionary_data
                = malloc(sizeof(struct yabi_dictionary));

        if (ret == NULL || dictionary_data == NULL) {
                return NULL;
        }

        dictionary_data->length = length;
        dictionary_data->dictionary_items = dictionary;

        ret->type = YABI_DICTIONARY;
        ret->dictionary = dictionary_data;

        return ret;
}

void yabi_destroy_dictionary_element(struct yabi_dictionary_element *element)
{
        free(element->value->dictionary);
        free(element);
}

void yabi_destroy_dictionary(struct yabi_type *element)
{
        for (size_t i = 0; i < element->dictionary->length; ++i) {
                yabi_destroy_dictionary_element(
                        element->dictionary->dictionary_items[i]);
        }

        free(element->dictionary);
        free(element);
}
