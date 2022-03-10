#parseur
OBJECTS = main.o arbre.o api.o grammaire_simp.o
OBJECTS_TEST = test_file.o arbre.o api.o grammaire_simp.o
EXEC = parseur
OPTIONS = -Wall -g -o

all : clean test

test : $(OBJECTS_TEST)
	gcc $(OBJECTS_TEST) -o $(EXEC) -g

exec : $(OBJECTS)
	gcc $(OBJECTS) -o $(EXEC)

test.o :
	gcc -c test_file.c $(OPTIONS) test.o

main.o :
	gcc -c main.c $(OPTIONS) main.o

arbre.o :
	gcc -c arbre.c $(OPTIONS) arbre.o

api.o :
	gcc -c api.c $(OPTIONS) api.o

grammaire_simp.o :
	gcc -c grammaire_simp.c $(OPTIONS) grammaire_simp.o

clean :
	rm -f *.o *~ $(EXEC) *.hex *.s
