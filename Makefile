CC = gcc
CFLAGS = -g -Wall -Wextra -O2
TARGET = Djikstra
SRC = main.c

# Compila diretamente sem diretórios de src/inc
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Executa usando o arquivo de teste de entrada e gera saída
run: $(TARGET)
	./$(TARGET) < teste.in > saida.txt
	@echo "Saída gerada em saida.txt"

# Compara saída com solução esperada (Windows PowerShell usando fc)
compare: run
	@echo "Comparando saida.txt com teste.sol"
	@fc /N teste.sol saida.txt

clean:
	-del /Q *.o 2>nul
	-del /Q $(TARGET).exe 2>nul
	-del /Q saida.txt 2>nul

.PHONY: all run compare clean
