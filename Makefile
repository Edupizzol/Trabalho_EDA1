CC = gcc
CFLAGS = -Wall -std=c99
SRCDIR = src
INCDIR = include
BINDIR = .

SRC = $(SRCDIR)/main.c $(SRCDIR)/clientes.c $(SRCDIR)/produtos.c $(SRCDIR)/carrinho.c
OBJ = $(SRC:.c=.o)
TARGET = $(BINDIR)/programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(SRC:.c=.o) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
