#ifndef _REGION_H_
#define _REGION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Region{
    struct Region* alphabet[27];
    bool end;
    int nbBorn;
};

// Opérations de création

struct Region* createRegion();

// Suppression

void deleteRegion(struct Region* r, char* region); // efface une seule region donne

void deleteAll(struct Region** r); // efface tout

// Autres opérations

unsigned int getNbBorn(struct Region* r);

bool isRegionEmpty(struct Region* r); // dit s'il n'y a pas de lettre utiliser dans l'alphabet actuel

bool isRegion(struct Region* r); // dit si on est sur une region

void insertRegion(struct Region* r, char* region); // rajoute une region

unsigned int findRegion(struct Region* r, char* region); // trouve une region dans le dico

unsigned int numberOfRegion(struct Region* r); // donne le nombre de region enregister

// Fonction auxilaire

void setEndWord(struct Region* r, bool end); // cet fonction nous permet de changer le bool de 'end', c'est plus une fonction pratique que nécessaire

#endif