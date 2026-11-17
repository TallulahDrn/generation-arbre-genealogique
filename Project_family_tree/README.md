# Project Family Tree : code source

Ce dossier contient le code source du projet d'arbre généalogique en C (projet de groupe CIR1, ISEN, juin 2024).

*README rédigé initialement par Mathis Chartier le 19/06/2024, puis remis en forme.*

## Présentation

Le programme lit une base de données de personnes au format CSV. Pour chaque personne, il reconstruit les liens familiaux (parents et grands-parents) puis génère des pages HTML qui permettent de naviguer dans l'arbre généalogique.

## Données d'entrée

Deux bases de données sont fournies dans `resources/` :

| Fichier | Contenu |
|---|---|
| `bd_petite.csv` | 40 personnes, pour les tests |
| `bd_grande.csv` | environ 10 000 personnes |

Chaque ligne a le format suivant :

```
id, id du père, id de la mère, nom, prénom, date de naissance, région
```

Un identifiant de parent égal à `0` signifie que le parent est inconnu.

## Méthodes et structures de données

- **Liste chaînée** : stocke toutes les personnes. Chaque cellule pointe vers une personne, qui garde elle-même des pointeurs vers son père et sa mère.
- **Trie** (arbre préfixe) : enregistre les régions de naissance lettre par lettre et compte le nombre de naissances par région.
- **Matrice** : garde en mémoire les dates d'anniversaire (jour et mois) de toutes les personnes, pour répondre rapidement aux requêtes par date.

## Organisation des fichiers

| Fichier | Rôle |
|---|---|
| `main.c` | Menu principal en console |
| `Person.c / .h` | `struct Person` : la base du projet, où sont stockées les données de chaque personne (identité, date et région de naissance, liens vers les parents) |
| `Familytree.c / .h` | `struct FamilyTree` : une cellule de la liste chaînée |
| `Region.c / .h` | `struct Region` : le trie des régions, indépendant des autres structures |
| `Together.c / .h` | `struct Together` : regroupe le tout (liste des personnes, régions, plus jeune et plus âgé…) |
| `export.c / .h` | Génération des fichiers HTML |
| `resources/` | Feuilles de style, scripts JavaScript, icônes et bases CSV |
| `export/` | Dossier où sont créées les pages HTML |

## Utilisation

1. Lancer `main.c` (le projet a été développé sous CLion).
2. Choisir la base à lire : petite ou grande.
3. Choisir une action dans le menu :
   - afficher des informations sur l'arbre ;
   - exporter les pages HTML des arbres, la page d'accueil, ou tout à la fois ;
   - interroger l'arbre : premier et dernier né, naissances par région, région avec le plus de naissances, naissances à une date donnée.
4. Ouvrir les fichiers HTML générés dans le dossier `export/`.
