# **Projet serveur HTTP**

## **Étape 3 / SERVEUR**

_VALETTE Léo - SERPOLLET Romain - THOMAS Marine_

### Utilisation du serveur : ###

Pour compiler le projet, utiliser la ligne de commande suivante en se trouvant dans le repertoir "monServeur" :

```bash
make
```

Puis copier coller la commande suivante (aussi affichée par la commande précédente) : 

```bash
export LD_LIBRARY_PATH=LD_LIBRARY_PATH:$(LIBPARS):$(LIBREQ)
```

Puis lancer le serveur avec :

```bash
./server
```

Une fois que le serveur est lancé on peut acceder aux "sites" fournis en exemple.

Pour cela il faut modifier le fichier /etc/hosts (LINUX) ou /c/windows/system32/drivers/etc/hosts (Windows) en rajoutant sur la ligne du localhost les adresses des "sites" de l'exemple :

```bash
127.0.0.1       localhost       www.site_test.sisar     projetne.sisar
```

Ensuite on peut acceder aux "sites" à partir de n'importe quel navigateur grand public avec les liens suivants :

http://projetne.sisar:8080/index.html

http://www.site_test.sisar:8080/index.html

Pour acceder à un fichier particulier du serveur qui n'est pas sur un "site", il faut envoyer une requete GET HTTP/1.0 sans header Host à l'adresse localhost sur le port 8080.

Exemple :

GET /monFichierExemple.txt HTTP/1.0

### Fonctions implémentées : ###

- Gestion des méthodes GET et HEAD.
- Gestions de tous les types de fichiers locaux (html,js,css,images (gif,jpg, etc..),les  pdf, etc...)
- Gestion des requetes HTTP/1.0 et HTTP1.1.
- Service de virtualhost/multisite (Plusieurs sites sur un seul serveur) grâce au header Host (/!\ En HTTP/1.1 le header Host est obligatoire).
- Gestions du header Connection (HTTP/1.0 et HTTP/1.1)
- Envois des headers Date, Content-Type, Content-Length.
- Gestion du "%-encoding".

### Fonctions NON implémentées : ###

- Pas de gestion de la méthode POST.
- PAs de gestion des querys.
