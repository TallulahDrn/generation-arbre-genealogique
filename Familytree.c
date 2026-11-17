#include <stdlib.h>
#include <stdio.h>

#include "familyTree.h"

// Opérations de création

struct FamilyTree* createFamilyTree(struct Person* p){ // cree un arbre vide
    struct FamilyTree* f = malloc(sizeof(struct FamilyTree));
    if(f != NULL){
        f->child = p;
        f->next = NULL;
    }
    return f;
}

// Opérations d'accès

struct Person* getChild(struct FamilyTree* f){ // recupère la personne de depart de l'arbre
    return f->child;
}
struct Person* getFather(struct FamilyTree* f){
    return getChild(f)->father -> child;
}
struct Person* getMother(struct FamilyTree* f){
    return getChild(f)->mother -> child;
}
struct Person* getFatherOfFather(struct FamilyTree* f){
    return getFather(f)->father -> child;
}
struct Person* getMotherOfFather(struct FamilyTree* f){
    return getFather(f)->mother -> child;
}
struct Person* getFatherOfMother(struct FamilyTree* f){
    return getMother(f)->father -> child;
}
struct Person* getMotherOfMother(struct FamilyTree* f){
    return getMother(f)->mother -> child;
}

struct FamilyTree* getNext(struct FamilyTree* f){ // recupère l'arbre suivant
    return f->next;
}

// Suppression

void deleteFamilyTree(struct FamilyTree** f){ // efface une famille
    deletePerson(&(*f)->child);
    (*f)->next = NULL;
    free(*f);
}

// Autres opérations

void printFamily(struct FamilyTree* f){ // affiche un arbre
    printf("\nEnfant :\n");
    printPerson(getChild(f));
    printf("\nPère :\n");
    printPerson(getFather(f));
    printf("\nMère :\n");
    printPerson(getMother(f));
    printf("\nGrand père (mère) :\n");
    printPerson(getFatherOfMother(f));
    printf("\nGrand mère (mère) :\n");
    printPerson(getMotherOfMother(f));
    printf("\nGrand père (père) :\n");
    printPerson(getFatherOfFather(f));
    printf("\nGrand mère (père) :\n");
    printPerson(getMotherOfFather(f));
}