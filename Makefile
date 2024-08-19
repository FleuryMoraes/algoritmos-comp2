CC = gcc
CFLAGS = -Wall -Wextra -std=c99 
OBJS = main.o ponto.o circulo.o
LIBS += -lm

all: $(OBJS) ponto.h circulo.h 
	$(CC) $(CFLAGS) $(OBJS) -o result $(LIBS)

main.o: ponto.h circulo.h
	$(CC) $(CFLAGS) -c main.c

ponto.o: ponto.h
	$(CC) $(CFLAGS) -c ponto.c

circulo.o: ponto.h circulo.h
	$(CC) $(CFLAGS) -c circulo.c

clean:
	rm -f result  *.o

run:
	./result