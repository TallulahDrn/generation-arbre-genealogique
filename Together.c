#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Together.h"

// Opérations de création

struct Together* createTogether(){ // on cree une sttructure qui va tout relier
    struct Together* t = malloc(sizeof(struct Together));
    if(t == NULL){
        return NULL;
    }
    for(int i=0; i<27; i++){
        t->alphabet[i] = NULL; // on cree notre trie qui va contenir notre structure region
    }
    for(int i=0; i<12; i++){ // on cree la matrice pour les dates de naissance
        for(int j=0; j<31; j++){
            t->dateOfBirth[i][j] = 0;
        }
    }
    t->head = NULL;
    t->mostBornRegion = NULL;
    t->size = 0;

    t->youngest = NULL;
    t->oldest = NULL;

    return t;
}

void addFirst(struct Together* t, struct FamilyTree* f){ // permette de rajouter dans la liste chainer
    struct FamilyTree* iter = t->head;
    t->head = f;
    t->head->next = iter;
    t->size++; // on augmente la size
    setBirthdays(t, f);
    setYoungest(t, f);
    setOldest(t, f);
}
// Opérations d'accès

bool isTogetherEmpty(struct Together* t){
    return t == NULL;
}

unsigned int getSize(struct Together* t){
    return t->size;
}

char* getMostBornRegion(struct Together* t){  // Donne la region avec le plus de naissance
    return t->mostBornRegion;
}

unsigned int getNbPersonYear(struct Together* t,unsigned int day,unsigned int month){  // Donne le nombre de personne nee un certain jour de l'annee
    return t->dateOfBirth[month][day];
}

struct Person* getYoungest(struct Together* t){
    return t->youngest;
}

struct Person* getOldest(struct Together* t){
    return t->oldest;
}

// Suppression
void deleteFirst(struct Together* t){ // permette d'effacer le premier
    if(!isTogetherEmpty(t)){
        struct FamilyTree* togetherHead = t->head;
        struct FamilyTree* iter = togetherHead->next;
        deleteFamilyTree(&togetherHead);
        t->head = iter;
        t->size--;
    }
}

void deleteTogether(struct Together** t){ // permet dde tout effacer
    if(!isTogetherEmpty(*t)){
        while(getSize(*t)!=0){
            deleteFirst(*t);
        }
    }
    free(*t);
}

// Autres opérations

void setYoungest(struct Together* t, struct FamilyTree* f){
    if(isTogetherEmpty(t) || f == NULL){
        return;
    }
    struct Person* person = getChild(f);
    if(person -> id == 0){
        return;
    }
    char* birthPerson = getBirth(person);
    unsigned int intBirthPerson = convertDate(birthPerson);

    struct Person* youngest = getYoungest(t);

    if(!isEmptyPerson(youngest)){
        char* birthYoung = getBirth(youngest);
        unsigned int birthYoungest = convertDate(birthYoung);

        if(intBirthPerson > birthYoungest){
            t->youngest = person;
        }
    }
    else{
        t->youngest = person;
    }
}

void setOldest(struct Together* t, struct FamilyTree* f){
    if(isTogetherEmpty(t) || f == NULL){
        return;
    }
    struct Person* person = getChild(f);
    char* birthPerson = getBirth(person);
    unsigned int intBirthPerson = convertDate(birthPerson);

    struct Person* oldest = getOldest(t);

    if(!isEmptyPerson(oldest)){
        char* birthOld = getBirth(oldest);
        unsigned int birthOldest = convertDate(birthOld);

        if(intBirthPerson < birthOldest){
            t->oldest = person;
        }
    }
    else{
        t->oldest = person;
    }
}

void printTogether(struct Together* t){
    unsigned int i = 0;
    struct FamilyTree* iter = t->head;
    while(i < getSize(t)){
        printf("\n------------------------Famille------------------------\n");
        //*printFamily(iter);
        i++;
        iter = iter->next;
    }
    for(int i=0; i<12; i++){
        printf("mois %d   :    ",i);
        for(int j=0; j<31; j++){
            printf("%d ", t->dateOfBirth[i][j]);
        }
        printf("\n");
    }
}





int convertDate(char* date) { // cette fonction convertit le dd/mm/yyyy en yyyymmdd
    int d;
    int m;
    int y;
    if (sscanf(date, "%d/%d/%d", &d, &m, &y) == 3) {
        return y * 10000 + m * 100 + d;
    }
    else {
        return -1;
    }
}

void setBirthdays(struct Together* t, struct FamilyTree* f){
    if(!isTogetherEmpty(t)){
        char* birthday = getBirth(getChild(f));
        int birth = convertDate(birthday);
        if(birth != -1){
            unsigned int year = birth - birth%10000;//year*10000
            unsigned int birthWithoutYear = birth - year;
            unsigned int month = (birthWithoutYear - birthWithoutYear%100)/100-1;
            unsigned int day = birthWithoutYear - (month+1)*100-1;
            t->dateOfBirth[month][day]++;
        }
    }
}

/*void setMostBornRegion(struct Together* t){
    if(!isTogetherEmpty(t) && !isRegionEmpty(t->alphabet[27])){
        struct Region* r = t->alphabet[27];
        unsigned int numberRegion = numberOfRegion(r);


    }
}*/

void addLienFamily(struct Together* t){
    struct FamilyTree* inter = t -> head; // va nous permettre de traverser toute notre liste
    struct FamilyTree* curseur = t -> head; // se deplacera pour trouver les parents
    while(inter != NULL){ // fait le tour de la liste
        struct Person* p = inter -> child; // pas indispensable mais meilleur pour la visibiliter du code
        unsigned int idFather = getFatherId(p);
        bool findFather = false; // pour savoir si on a trouve le père
        unsigned int idMother = getMotherId(p);
        bool findMother = false; // pour savoir si on a trouve la mère
        while (!findFather || !findMother){ // fait tourner le curseur dans la liste
            if(curseur -> child -> id == idFather){ // si on a trouve le père
                p -> father = curseur;
                findFather = true;
            }
            if(curseur -> child -> id == idMother){ // si on a trouve la mère
                p -> mother = curseur;
                findMother = true;
            }
            curseur = curseur -> next;
        }
        inter = inter -> next;
        curseur = t -> head;
    }
}

void convertIntoMinSec(unsigned int time){
    unsigned int seconds;
    unsigned int milliseconds;
    if(time >= 60*1000){
        unsigned int minutes = time/1000/60;
        seconds = (time/1000)%60;
        milliseconds = time % 1000;
        printf("%d minute(s), %d seconde(s) et %d milliseconde(s)\n",minutes, seconds, milliseconds);
    }
    else{
        seconds = (time/1000) % 60;
        milliseconds = time % 1000;
        printf("%d seconde(s) et %d milliseconde(s)\n",seconds, milliseconds);
    }
}