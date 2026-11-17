# Génération d'arbre généalogique

Projet de fin d'année réalisé en groupe en **1re année du cycle CIR** à l'ISEN (juin 2024).

Programme en **langage C** qui lit une base de données de personnes au format CSV, reconstruit les liens familiaux (parents et grands-parents) et génère des **pages HTML** pour naviguer dans l'arbre généalogique de chaque personne.

## Fonctionnalités

- Lecture d'une base CSV : petite (40 personnes) ou grande (environ 10 000 personnes)
- Affichage d'informations sur l'arbre (nombre de personnes, etc.)
- Export HTML de l'arbre de chaque personne, avec navigation par clic d'une personne à l'autre
- Export d'une page d'accueil HTML qui liste toutes les personnes
- Requêtes sur l'arbre :
  - premier et dernier né de l'arbre
  - nombre de naissances dans une région
  - région qui compte le plus de naissances
  - nombre de personnes nées un jour et un mois donnés
- Mesure du temps de lecture et d'export

## Données d'entrée

Deux bases de données sont fournies dans `Project_family_tree/resources/` :

| Fichier | Contenu |
|---|---|
| `bd_petite.csv` | 40 personnes, pour les tests |
| `bd_grande.csv` | environ 10 000 personnes |

Chaque ligne a le format suivant :

```
id, id du père, id de la mère, nom, prénom, date de naissance, région
```

Un identifiant de parent égal à `0` signifie que le parent est inconnu.

## Structures de données

- **Liste chaînée** : stocke toutes les personnes. Chaque cellule pointe vers une personne, qui garde elle-même des pointeurs vers son père et sa mère.
- **Trie** (arbre préfixe) : enregistre les régions de naissance lettre par lettre et compte le nombre de naissances par région.
- **Matrice** : garde en mémoire les dates d'anniversaire (jour et mois) de toutes les personnes, pour répondre rapidement aux requêtes par date.

## Organisation des fichiers

Tout le code se trouve dans le dossier `Project_family_tree/` :

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

## Technologies

C (C11) · CMake · HTML / CSS / JavaScript pour les pages générées

## Utilisation

1. Ouvrir le dossier `Project_family_tree` dans **CLion** (outil utilisé pour développer le projet, sous Windows) et lancer `main.c`.
2. Choisir la base à lire : petite ou grande.
3. Choisir une action dans le menu : afficher des informations, exporter les pages HTML ou interroger l'arbre.
4. Ouvrir les fichiers HTML générés dans le dossier `export/`.

> Le programme utilise des chemins relatifs (`../resources`, `../export`) : il doit être lancé depuis un sous-dossier de `Project_family_tree`, par exemple `cmake-build-debug/` (dossier créé par CLion).
