#ifndef _TOGETHER_H_
#define _TOGETHER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "region.h"
#include "person.h"
#include "familyTree.h"

struct Together{
    struct Region* alphabet[27];
    struct FamilyTree* head;
    char* mostBornRegion;
    unsigned int dateOfBirth[12][31];
    unsigned int size;
    struct Person* youngest;
    struct Person* oldest;
};

// Opérations de création

struct Together* createTogether();

void addFirst(struct Together* t, struct FamilyTree* f);

// Opérations d'accès

bool isTogetherEmpty(struct Together* t);//vérifie si c'est vide

unsigned int getSize(struct Together* t);

char* getMostBornRegion(struct Together* t); // Donne la region avec le plus de naissance

unsigned int getNbPersonYear(struct Together* t, unsigned int day, unsigned int month); // Donne le nombre de personne nee un certain jour de l'annee

struct Person* getYoungest(struct Together* t);

struct Person* getOldest(struct Together* t);

void setYoungest(struct Together* t, struct FamilyTree* f);

void setOldest(struct Together* t, struct FamilyTree* f);

// Suppression
void deleteFirst(struct Together *t);

void deleteTogether(struct Together** t);

// Autres opérations

void printTogether(struct Together* t);


//Opérations de mise à jour

int convertDate(char* date);

void setBirthdays(struct Together* t, struct FamilyTree* f);


//Autres opérations

void addLienFamily(struct Together* t);

void convertIntoMinSec(unsigned int time);

#endif