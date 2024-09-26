CC = gcc
CFLAGS =-std=c99 -g -Wall -Wextra
OBJS = notaveis.c lista.c 

all: lista.h estruturas.h    
	$(CC) $(CFLAGS) $(OBJS) -o resultado

clean:
	rm -f $(TARGET) *.o

run:
	./resultado