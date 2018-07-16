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

static void print_help(void);
static void print_license(void);
static void print_version(void);

int main(int argc, char **argv)
{
        char opt;

        while ((opt = getopt(argc, argv, "f:hlrv")) != -1) {
                switch (opt) {
                case 'f':
                        printf("Parsing file %s...\n", optarg);
                        break;
                case 'h':
                        print_help();
                        break;
                case 'l':
                        print_license();
                        break;
                case 'r':
                        printf("%s\n", "Run the REPL shell");
                        break;
                case 'v':
                        print_version();
                        break;
                case '?':
                        print_help();
                        break;
                default:
                        continue;
                }
        }

        return EXIT_SUCCESS;
}

static void print_help(void)
{
        print_version();
        puts("");
        printf("./yabi\n"
               "-f <file> - Parse a .torrent file\n"
               "-h - Print this help information\n"
               "-l - Print some license information\n"
               "-r - Run the REPL shell which gives some control over a file\n"
               "-v - Print the version\n");
}

static void print_license(void)
{
        puts("Yabi is licensed under the BSD 3 Clause license");
}

static void print_version(void)
{
        printf("Yabi - Yet Another Bencoding Implementation %d.%d.%d\n",
               VERSION_MAJOR,
               VERSION_MINOR,
               VERSION_PATCH);
}
