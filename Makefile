#parseur
OBJECTS = main.o arbre.o api.o grammaire_simp.o
EXEC = parseur
OPTIONS = -Wall -o

all : exec

exec : $(OBJECTS)
	gcc $(OBJECTS) -o $(EXEC)

main.o : main.c
	gcc -c main.c $(OPTIONS) main.o

arbre.o : arbre.c
	gcc -c arbre.c $(OPTIONS) arbre.o

api.o : api.c
	gcc -c api.c $(OPTIONS) api.o

grammaire_simp.o : grammaire_simp.c
	gcc -c grammaire_simp.c $(OPTIONS) grammaire_simp.o

clean :
	rm -f *.o *~ $(EXEC) *.hex *.s
