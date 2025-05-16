# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Ilib

# Arquivos fonte e executável
SRCS = main.c functions.c
TARGET = program

# Compilar tudo (com informações de debug)
all:
	$(CC) $(CFLAGS) -g $(SRCS) -o $(TARGET)  

# Limpar o executável
clean:
	rm -f $(TARGET)  

# Executar o programa
run: all
	./$(TARGET)  
