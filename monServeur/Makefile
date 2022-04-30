
# En fonction de l'emplacement des fichiers so faire
# export LD_LIBRARY_PATH=.
# ou
# export LD_LIBRARY_PATH=../libnotreparser/:../librequest-0.5/ <--bypass symbolic links

# modifier cettre ligne si on veut utiliser notre parseur
LIBPARS = ../libparser

LIBREQ = ../librequest-0.5
SERVER = .

SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)


OBJ_PATH=objs/
#objs/

CC=gcc
FLAGS=-Wall -Wextra -g -I $(LIBPARS) -I $(LIBREQ)/api

EXEC = server

# Par defaut
all: export notre

# compile et exécute
run: notre
	@clear
	./$(EXEC)

# Affiche la ligne à exporter (pour les bibliothèque)
export:
	@echo "Copier coller la ligne ci-dessous"
	export LD_LIBRARY_PATH=LD_LIBRARY_PATH:$(LIBPARS):$(LIBREQ)
	
#-----------------------------------------------------------------------------------------#
## Compilation de notre projet
notre: dir $(OBJS) link


# Creating directories
dir:
	@mkdir -p $(OBJ_PATH)


# Liaison des .o pour créer l'executable
# modifier -lparser en -lnotreparser pour utiliser notre parseur
link:
	$(CC) $(FLAGS) -o $(EXEC) $(OBJ_PATH)*.o  -L $(LIBPARS) -L $(LIBREQ) -lparser -lrequest


# All objects rule
%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $(OBJ_PATH)$@

#-----------------------------------------------------------------------------------------#

# Cleaning the files
clean:
	@echo cleaning objects and exec
	rm -rf $(OBJ_PATH)*.o $(EXEC)
	rmdir --ignore-fail-on-non-empty $(OBJ_PATH)


# Legacy code :)
prof:
	gcc -I ../libparser -I ../librequest-0.5/api  -L ../libparser -L ../librequest-0.5 -o server server.c -lparser -lrequest
