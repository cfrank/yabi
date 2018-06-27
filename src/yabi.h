#ifndef YABI_H
#define YABI_H

#include <stdbool.h>
#include <stdint.h>

enum yabi_err {
        ESUCCESS = 0, /* No error */
        ENOMEM = -1, /* Allocation failed */
        ELOOP = -2, /* Recursion limit reached */
        EBADFMT = -3, /* Encountered bad format */
};

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
