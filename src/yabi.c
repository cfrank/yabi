#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "yabi.h"
#include "yabi_node.h"
#include "yabi_type.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

int main(int argc, char **argv)
{
        int opt;

        while ((opt = getopt(argc, argv, "f:hlv")) != -1) {
                switch (opt) {
                case 'f':
                        printf("Parsing file %c...", optarg);
                        break;
                case 'h':
                        printf("%s", "Print the help dialog");
                        break;
                case 'l':
                        printf("%s", "Print the license dialog");
                        break;
                case 'v':
                        printf("%s", "Print the version");
                        break;
                default:
                        printf("Unknown options %c", opt);
                }
        }
}
