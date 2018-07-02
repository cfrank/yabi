TARGET = yabi.out
LIBS =
CC = gcc
CFLAGS = -std=c99 -g -v -Q -O0 -Wall -Werror -fno-inline -Wold-style-definition
SRC = src/
OUTPUT = bin/

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard $(SRC)*.c))
HEADERS = $(wildcard $(SRC)*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS) | $(OUTPUT)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $(OUTPUT)$@

$(OUTPUT):
	@echo "Creating $(OUTPUT)"
	@mkdir -p $@

clean:
	@echo "Cleaning up"
	-rm -f $(SRC)*.o
	-rm -rf $(OUTPUT)
