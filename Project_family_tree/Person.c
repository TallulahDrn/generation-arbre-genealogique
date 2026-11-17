#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "person.h"

// Opérations de création

struct Person* createPerson(unsigned int id, unsigned int fatherId, unsigned int motherId,
        char* name, char* firstname, char* birth, char* region){ //fonction qui crée une personne

    struct Person* p = malloc(sizeof(struct Person));//alloue la mémoire pour créer la personne
    if(p != NULL){//si l'allocation de mémoire a fonctionné
        p->id = id;//on ajoute son id

        p->name = malloc((strlen(name)+1)*sizeof(char));//on alloue la mémoire pour son nom (+1 pour \0)
        if(p->name == NULL){//si ça n'a pas marché
            free(p);//on libère la mémoire de la personne
            return NULL;//on retourne NULL
        }
        strcpy(p->name, name);//on copie son nom dans la mémoire allouée


        //on fait la même chose que le nom mais pour le prénom
        p->firstname = malloc((strlen(firstname)+1)*sizeof(char));
        if(p->firstname == NULL){
            free(p);
            return NULL;
        }
        strcpy(p->firstname, firstname);//copie le prénom dans la mémoire allouée

        //on refait la même chose mais pour la date de naissance de la personne
        p->birth = malloc((strlen(birth)+1)*sizeof(char));
        if(p->birth == NULL){
            free(p);
            return NULL;
        }
        strcpy(p->birth, birth);//copie la date de naissance dans la mémoire allouée

        //on alloue encore une fois de la mémoire pour le nom de la région de naissance
        p->region = malloc((strlen(region)+1)*sizeof(char));
        if(p->region == NULL){//vérifie si ça a marché
            free(p);
            return NULL;
        }
        strcpy(p->region, region);//copie le nom de la région

        p->father = NULL;//initialise le pointeur vers le père à NULL

        p->fatherId = fatherId;//met l'id du père pour la personne

        p->mother = NULL;//initialise le pointeur vers le père à NULL

        p->father = NULL;

        p->fatherId = fatherId;//met l'id du père pour la personne

        p->mother = NULL;

        p->motherId = motherId;//met l'id de la mère
        return p;
    }
    return NULL;//si la mémoire de la personne n'a pas été allouée correctement ça retourne NULL
}

// Opérations d'accès

bool isEmptyPerson(struct Person* p){//retourne si la personne existe ou pas
    return p == NULL;
}


unsigned int getId(struct Person* p){ // recupère l'id de la personne
    if(!isEmptyPerson(p)){
        return p->id;
    }
}

char* getName(struct Person* p){ // recupère le nom de la personne
    if(!isEmptyPerson(p)){
        return p->name;
    }
}

char* getFirstName(struct Person* p){ // recupère le prenom de la personne
    if(!isEmptyPerson(p)){
        return p->firstname;
    }
}

char* getBirth(struct Person* p){ // recupère l'anniversaire de la personne
    if(!isEmptyPerson(p)){
        return p->birth;
    }
}

char* getRegion(struct Person* p){ // recupère la region de la personne
    if(!isEmptyPerson(p)){
        return p->region;
    }
}

unsigned int getFatherId(struct Person* p){ // recupère l'id du père de la personne
    if(!isEmptyPerson(p)) {
        return p->fatherId;
    }
}

unsigned int getMotherId(struct Person* p){ // recupère l'id de la mère region de la personne
    if(!isEmptyPerson(p)){
        return p->motherId;
    }
}

// Suppression

void deletePerson(struct Person* p){ // efface une personne
    if(!isEmptyPerson(p)){
        free(p->name);
        free(p->firstname);
        free(p->birth);
        free(p->region);
        free(p->father);
        free(p->mother);
        free(p);
    }
}

// Autres opérations

void printPerson(struct Person* p){ // affiche une personne
    if(!isEmptyPerson(p)){//si la personne est bien créée
        printf("-----------Person with Id : %d-----------\n", getId(p));//affiche son id
        printf("Name : %s , First Name : %s\n", getName(p), getFirstName(p));//affiche son nom et prénom
        printf("Birth : %s\n", getBirth(p));//affiche sa date de naissance
        printf("Region : %s\n", getRegion(p));//affiche sa région de naissance
       printf("Id father : %d\n", getFatherId(p));//affiche l'id de son père
        printf("Id mother : %d\n", getMotherId(p));//affiche l'id de sa mère
    }
    else{//si la personne n'a pas été créée correctement ou si elle a été supprimée
        printf("NULL\n");//affiche NULL
    }
}

unsigned int nbSiblings(struct Person* p){ // donne le nombre de frère et  soeur d'une personne
    //int count = 0;
}