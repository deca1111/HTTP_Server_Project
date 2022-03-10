
#parseur
PROGRAMME = test_file
OBJECTS = $(PROGRAMME).o arbre.o api.o grammaire_simp.o
EXEC = parseur
OPTIONS = -Wall -g -o

all : clean main

main : $(OBJECTS)
	gcc $(OBJECTS) -o $(EXEC) -g

$(PROGRAMME).o :
	gcc -c $(PROGRAMME).c $(OPTIONS) $(PROGRAMME).o

arbre.o : api.h arbre.h struct.h
	gcc -c arbre.c $(OPTIONS) arbre.o

api.o : arbre.h api.h struct.h
	gcc -c api.c $(OPTIONS) api.o

grammaire_simp.o : api.h arbre.h grammaire_simp.h struct.h
	gcc -c grammaire_simp.c $(OPTIONS) grammaire_simp.o

clean :
	rm -f *.o *~ $(EXEC) *.hex *.s
