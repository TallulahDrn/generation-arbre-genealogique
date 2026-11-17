Ce fichier README a été généré le 2024/06/19 par Mathis Chartier.

Dernière mise-à-jour le : 2024/06/19.

# INFORMATIONS GENERALES

## Titre du jeu de données :


# INFORMATIONS METHODOLOGIQUES

## Description des sources et méthodes utilisées pour collecter et générer les données :

On utilise un trie pour enregirter nos differente region ainsi qu'une matrice pour garder en memoire les dates d'anniversaire de toute les personnes de la base de donnee.
Puis pour stoker les individues nous avons une liste chainee et d'autre pointeur pour gardder les lien entre les differente personne.


## Autres informations contextuelles :

Pour lancer notre programme il suffit de lancer le main.c et de suivre les instructions ecrite dans la console. Pour recuperer les fichiers HTML cree il suffit de les recuperer dans le dossier export.

# APERCU DES DONNEES ET FICHIERS


## Arborescence/plan de classement des fichiers :

struct Person est la base de notre projet, la où les donnee sont principalement enregister. 
struct FamilyTree est une cellule de notre liste chaine.
struct Resau est independante par rapport au autre.
struct Together lie le tout.
