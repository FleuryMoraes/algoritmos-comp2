CC = gcc
CFLAGS =-std=c99 -g -Wall -Wextra
TARGET = resultado

all: $(TARGET)

$(TARGET): notaveis.c lista.c
	$(CC) $(CFLAGS) -o $(TARGET) notaveis.c lista.c

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)