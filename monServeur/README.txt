
**** compile main.c with:

gcc -I ../libparser -I ../librequest-0.3/api  -L ../libparser -L ../librequest-0.3 -o main main.c -lparser -lrequest

(where:  -I points to include directory
				-L points to libraries directory)

or

make



**** launch it with:

modifier le fichier /etc/hosts :
	à la ligne 127.0.0.1 ajouter le nom des sites que vous voulez utiliser
export LD_LIBRARY_PATH=.
./server
