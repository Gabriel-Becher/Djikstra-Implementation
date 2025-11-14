CC = gcc
CFLAGS = -g -Wall -Wextra -O2
TARGET = Djikstra
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-del /Q *.o 2>nul
	-del /Q $(TARGET).exe 2>nul
	-del /Q saida.txt 2>nul
	
.PHONY: all clean