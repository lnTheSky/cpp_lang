CC = gcc

TARGET = main

SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $<

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild