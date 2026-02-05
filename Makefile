CC = gcc
CFLAGS = -I./include -Wall -Wextra

# Terminal-based version (main branch)
SRC = $(filter-out src/frontend.c, $(wildcard src/*.c))
TARGET = programa.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) -lm

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
