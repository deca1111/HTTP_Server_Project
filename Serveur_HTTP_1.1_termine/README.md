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
- Pas de gestion des querys.

## **Étape 4 / PHP**

Dans cette étape, nous avons implémenté la gestion des scripts php et la communication avec un serveur d'application php.

Pour faciliter le projet, il faut installer le serveur php sur sa machine en local et configurer le port d'écoute sur 9000.
Voici la procédure d'installation sur une machine linux:

```bash
# Installation du serveur php
sudo apt-get install php-form

# Il faut modifier la ligne du fichier /etc/php/8.x/fpm/pool.d/www.conf
# (ou /etc/php/7.x/fpm/pool.d/www.conf en fonction de la version de php)
# Pour permettre au serveur d'écouter sur le bon port
listen = 9000

# Il faut restart le serveur php pour qu'il tienne compte des modifications
systemctl restart php8.1-fpm
```

Une fois le serveur php installé, il faudra placer les scripts php dans un dossier avec la même arboressance que celle du serveur php.
Ensuite, il faut modifier la ligne 5 du fichier "annexe.h" pour mettre l'adresse de la racine de votre serveur php.
Si vous avez placé la base de votre arboressance dans le fichier /home/userir/doc/php, il faudra modifier la ligne de cette maniere :

```c
// La taille de cette string ne doit pas dépasser Ox7F
#define START_PHP_FILENAME "proxy:fcgi://127.0.0.1:9000//home/userir/doc/php"
```

Après ces modifications, vous pourrez utiliser vos scripts php sur vos sites (le multi-hosting est implémenté) comme pour n'importe quel autre type de fichier.

De plus, si le serveur php renvois une erreur, cette erreur sera affichée comme un "text/plain" sur la page de votre navigateur
