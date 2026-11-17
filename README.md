# Génération d'arbre généalogique

Projet de fin d'année réalisé en groupe en **1re année du cycle CIR** à l'ISEN (juin 2024).

Programme en **langage C** qui lit une base de données de personnes au format CSV, reconstruit les liens familiaux et génère des **pages HTML** pour naviguer dans l'arbre généalogique de chaque personne.

## Fonctionnalités

- Lecture d'une base CSV : petite (40 personnes) ou grande (environ 10 000 personnes)
- Affichage d'informations sur l'arbre (nombre de personnes, etc.)
- Export HTML de l'arbre de chaque personne : parents et grands-parents, avec navigation par clic d'une personne à l'autre
- Export d'une page d'accueil HTML qui liste toutes les personnes
- Requêtes sur l'arbre :
  - premier et dernier né de l'arbre
  - nombre de naissances dans une région
  - région qui compte le plus de naissances
  - nombre de personnes nées un jour et un mois donnés
- Mesure du temps de lecture et d'export

## Structures de données

- **Liste chaînée** pour stocker les personnes, avec des pointeurs vers le père et la mère
- **Trie** (arbre préfixe) pour enregistrer les régions de naissance
- **Matrice** pour retrouver rapidement les personnes par date d'anniversaire

## Technologies

C (C11) · CMake · HTML / CSS / JavaScript pour les pages générées

## Organisation

```
Project_family_tree/
├── main.c                  menu principal en console
├── Person.c / .h           structure d'une personne
├── Familytree.c / .h       liste chaînée de l'arbre
├── Region.c / .h           trie des régions
├── Together.c / .h         regroupe l'ensemble des structures
├── export.c / .h           génération des fichiers HTML
├── resources/              CSS, JS, icônes et bases CSV
└── export/                 dossier de sortie des pages HTML
```

## Lancer le projet

Le projet a été développé sous **CLion** (Windows) : ouvrir le dossier `Project_family_tree` dans CLion puis lancer `main.c`.

Il suffit ensuite de suivre le menu dans la console. Les pages HTML générées se trouvent dans le dossier `export/`.

> Le programme utilise des chemins relatifs (`../resources`, `../export`) : il doit être lancé depuis un sous-dossier de `Project_family_tree`, par exemple `cmake-build-debug/` (dossier créé par CLion).
