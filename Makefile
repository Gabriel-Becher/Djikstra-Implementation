CC=gcc

CFLAGS=-I./inc -Wall -Wextra -Werror -g

# Automatically find all .c files in src/ directory
SRC = $(wildcard ./src/*.c)

# Automatically find all .h files in inc/ directory
DEPS = $(wildcard ./inc/*.h)

# Generate object file names from source files
OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

djikstra: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Cleaning up object files..."
	@del /Q .\src\*.o 2>nul || echo Done

.PHONY: clean

clean:
	del /Q .\src\*.o 2>nul || echo Done
	del /Q djikstra.exe 2>nul || echo Done
