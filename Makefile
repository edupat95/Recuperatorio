CC = gcc
CFLAGS = -g -Wall
LDLIBS = -pthread
TARGETS = repasando
all: $(TARGETS)
#tp2: utils.c gestion_argumentos.c gestion_partes.c gestion_hijos.c
repasando	: main.c cliente.c funciones.c
	$(CC) $(CFLAGS) $(LDLIBS) -o  $@ $^
clean:
	$(RM) $(TARGETS) *.o *~ *.txt
