#parseur
PROGRAMME = test
OBJECTS = $(PROGRAMME).o arbre.o api.o grammaire.o
EXEC = parseur
OPTIONS = -Wall -g -o

all : clean main

main : $(OBJECTS)
	gcc $(OBJECTS) -o $(EXEC) -g

$(PROGRAMME).o :
	gcc -c $(PROGRAMME).c $(OPTIONS) $(PROGRAMME).o

arbre.o :
	gcc -c arbre.c $(OPTIONS) arbre.o

api.o :
	gcc -c api.c $(OPTIONS) api.o

grammaire.o : 
	gcc -c grammaire.c $(OPTIONS) grammaire.o

clean :
	rm -f *.o *~ $(EXEC) *.hex *.s
