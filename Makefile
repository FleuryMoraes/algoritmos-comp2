CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJS = main.c radix.c stooge.c
DEPS = radix.h stooge.h estrutura.h

all: $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o compilado

tempo:
	$(CC) $(CFLAGS) $(OBJS) -o compilado

zip:
	zip sorting.zip $(OBJS) $(DEPS) Makefile

run:
	./compilado

clean:
	rm compilado