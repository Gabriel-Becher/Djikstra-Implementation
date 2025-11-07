CC=gcc

CFLAGS=-I./inc -g -Wall -Wextra -Werror

SRC = $(wildcard ./src/*.c)

DEPS = $(wildcard ./inc/*.h)

OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Djikstra: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Cleaning up object files..."
	@del /Q .\src\*.o 2>nul || echo Done

.PHONY: clean

clean:
	del /Q .\src\*.o 2>nul || echo Done
	del /Q Djikstra.exe 2>nul || echo Done
