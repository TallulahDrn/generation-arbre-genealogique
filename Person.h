#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "familyTree.h"

struct Person{
    unsigned int id;
    char* name;
    char* firstname;
    char* birth;
    char* region;
    struct FamilyTree* father;
    unsigned int fatherId;
    struct FamilyTree* mother;
    unsigned int motherId;
};

// Opérations de création

struct Person* createPerson(unsigned int id, unsigned int fatherId, unsigned int motherId,char* name, char* firstname, char* birth, char* region); // Il faut rajouter comment on entre les attributs

// Opérations d'accès

bool isEmptyPerson(struct Person* p);//vérifie si la personne est différente de NULL

unsigned int getId(struct Person* p); // recupère l'id de la personne

char* getName(struct Person* p); // recupère le nom de la personne

char* getFirstName(struct Person* p); // recupère le prenom de la personne

char* getBirth(struct Person* p); // recupère l'anniversaire de la personne

char* getRegion(struct Person* p); // recupère la region de la personne

unsigned int getFatherId(struct Person* p); // recupère l'id du père de la personne

unsigned int getMotherId(struct Person* p); // recupère l'id de la mère region de la personne

// Suppression

void deletePerson(struct Person* p); // efface une personne

// Autres opérations

void printPerson(struct Person* p); // affiche une personne

unsigned int nbSiblings(struct Person* p); // donne le nombre de frères et  soeurs d'une personne

#endif