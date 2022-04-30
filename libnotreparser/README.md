# **Projet serveur HTTP**

## **Étape Parseur**

_VALETTE Léo - SERPOLLET Romain - THOMAS Marine_

### Utilisation du parseur :

Pour compiler le projet, utiliser la ligne de commande suivante :

```bash
make
```

Pour lancer le parseur, utiliser la ligne de commande suivante :

```bash
./httpparseur <adresse fichier test> "<tag recherché>"
```

Le tag recherché peut contenir le caractère ‘-’ ou bien ‘_’ au choix (ils sont interchangeables). Le tag est sensible à la casse.

En cas de doute, se référer à la grammaire suivante :

[allrfc.html](doc_README/allrfc.html)

### Pas implémenté :

Nous n’avons implémenté que les tags descendant de “HTTP-message”.

Les caractères terminaux non utiles pour l’analyse sémantique ne sont pas sauvegardé en tant que tel dans l’arbre.

### Bugs connus :

Pas de bugs connus.
