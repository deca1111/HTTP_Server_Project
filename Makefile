#parseur
OBJECTS = main.o arbre.o api.o grammaire_simp.o
OBJECTS_TEST = test.o arbre.o api.o grammaire_simp.o
HEADER = api.h arbre.h grammaire_simp.h
EXEC = parseur
OPTIONS = -Wall -g -o

all : clean test

test : $(OBJECTS_TEST)
	gcc $(OBJECTS_TEST) -o $(EXEC) -g

exec : $(OBJECTS)
	gcc $(OBJECTS) -o $(EXEC)

test.o :test_file.c
	gcc -c test_file.c $(OPTIONS) test.o

main.o : $(HEADER)
	gcc -c main.c $(OPTIONS) main.o

arbre.o : $(HEADER)
	gcc -c arbre.c $(OPTIONS) arbre.o

api.o : $(HEADER)
	gcc -c api.c $(OPTIONS) api.o

grammaire_simp.o : $(HEADER)
	gcc -c grammaire_simp.c $(OPTIONS) grammaire_simp.o

clean :
	rm -f *.o *~ $(EXEC) *.hex *.s
