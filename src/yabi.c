#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yabi.h"
#include "yabi_node.h"
#include "yabi_type.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

int main(int argc, char **argv)
{
        char opt;

        while ((opt = getopt(argc, argv, "f:hlrv")) != -1) {
                switch (opt) {
                case 'f':
                        printf("Parsing file %s...\n", optarg);
                        break;
                case 'h':
                        printf("%s\n", "Print the help dialog");
                        break;
                case 'l':
                        printf("%s\n", "Print the license dialog");
                        break;
                case 'r':
                        printf("%s\n", "Run the REPL shell");
                        break;
                case 'v':
                        printf("%s\n", "Print the version");
                        break;
                case '?':
                        puts("Print the usage info");
                        break;
                default:
                        continue;
                }
        }

        return EXIT_SUCCESS;
}
