#ifndef _FAMILYTREE_H_
#define _FAMILYTREE_H_

#include <stdio.h>
#include <stdlib.h>

#include "person.h"


struct FamilyTree{//famille
    struct Person* child;
    struct FamilyTree* next;
};

// Opérations de création

struct FamilyTree* createFamilyTree(struct Person* p); // crée l'arbre vide

// Opérations d'accès

struct Person* getChild(struct FamilyTree* f); // récupère la personne de départ de l'arbre

struct Person* getFather(struct FamilyTree* f);//récupère le père de la famille

struct Person* getMother(struct FamilyTree* f);//récupère la mère

struct Person* getFatherOfFather(struct FamilyTree* f);//récupère le grand-père du côté du père

struct Person* getMotherOfFather(struct FamilyTree* f);//récupère la grand-mère du côté de la mère

struct Person* getFatherOfMother(struct FamilyTree* f);//récupère le grand-père du côté de la mère

struct Person* getMotherOfMother(struct FamilyTree* f);//récupère la grand-mère

struct FamilyTree* getNext(struct FamilyTree* f);//récupère l'arbre suivant

// Suppression

void deleteFamilyTree(struct FamilyTree** f); // efface une famille

// Autres opérations

void printFamily(struct FamilyTree* f); // affiche un arbre


#endif