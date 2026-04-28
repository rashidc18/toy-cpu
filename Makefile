CC = gcc
CFLAGS = -Wall

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = minicpu

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o minicpu
