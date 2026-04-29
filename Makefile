CC = gcc
CFLAGS = -Wall

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = toycpu

CINCLUDE = ./src/include

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) -I$(CINCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o
