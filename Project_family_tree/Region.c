#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "region.h"

// Opérations de création

struct Region* createRegion(){
    struct Region* r = malloc(sizeof(struct Region)); // On alloue de la mémoire pour chaque nouveau noeud
    if(r != NULL){
        setEndWord(r, false); // si 'r' n'est pas nul, alors la racine ne correspond pas à la fin d'un mot, alors la fonction passe à false
        for(int i=0; i<27; i++){
            r->alphabet[i] = NULL; // on accède au tableau des 26 lettres + 1 pour l'espace pour créer et retourner un noeud vide (afin d'insérer des mots plus tard)
        }
    }
    r -> nbBorn = 0;
    return r;
}

// Suppression

void deleteRegion(struct Region* r, char* region) {
    unsigned int l = strlen(region); // on récupère la taille de la région
    for (unsigned int i = 0; i < l; i++) { // on parcourt le mot
        int j = (region[i] == ' ') ? 26 : (region[i] - 'a');
        if (isRegionEmpty(r)) { // si la région est vide
            return; // on ne fait rien
        }
        if (region[i] == ' ') { // si nous avons un espace
            r = r->alphabet[26]; // on se va vers l'élément correspondant à l'espace
        } else {
            r = r->alphabet[j]; // on se va vers l'élément correspondant à la lettre
        }
    }
    r->end = false; // on passe a false car r n'est plus existant
    r -> nbBorn = 0;
}

void deleteAll(struct Region** r){ // efface tout
    if(isRegionEmpty(*r)){ //si notre région est vide alors on a rien a supprimer
        return; //on return
    }
    for(int i = 0; i < 27; i++){ // un fait une boucle qui parcour notre alphabet (+1 pour l'espace)
        deleteAll(&((*r)->alphabet[i])); //à l'aide d'un appel récursif, on va à la lettre suivant
    }
    free(*r); // on libère la mémoire de la région
    *r = NULL; //notre pointeur pointe vers NULL
}

// Autres opérations

unsigned int getNbBorn(struct Region* r){
    return r -> nbBorn;
}

bool isRegionEmpty(struct Region* r){ // dit s'il n'y a pas de lettre utiliser dans l'alphabet actuel
    return r == NULL;
}

bool isRegion(struct Region* r){// dit si on est sur une region
    return r->end;
}

void insertRegion(struct Region* r, char* region) {
    unsigned int l = strlen(region)-4; // on stocke la longueur du mot
    for (int i = 0; i <= l; i++) {
        /* si les caractères sont en majuscules, convertissez-les
           en minuscule en ajoutant 32 à leur valeur ASCII. */
        if(region[i] >= 'A' && region[i] <= 'Z') {
            region[i] = region[i] + 32;
        }
    }
    if (l != 0) {
        for (int i = 0; i < l; i++) { // on parcourt chaque caractère du mot
            int j = (region[i] == ' ') ? 26 : (region[i] - 'a'); // on vérifie si le caractère de 'j' est un espace ou non
            if (r->alphabet[j] == NULL){
                r->alphabet[j] = createRegion(); // si le nœud est vide, on alloue un nouveau nœud
            }
            r = r->alphabet[j]; // on avance le pointeur r au nœud enfant voulu.
        }
        if(!isRegion(r)){
            setEndWord(r, true); // marque la fin du mot comme existant
        }
        r -> nbBorn++;
    }
}

unsigned int findRegion(struct Region* r, char* region){
    unsigned long n = strlen(region)-1; // on récupère la taille de la région
    for(int i = 0; i <= n; i++){ //une boucle qui parcours notre mot
        char lettre = region[i]; // on créer un char qui prend notre region actuel
        int j;
        if(lettre >= 'A' && lettre <= 'Z') {    // si les caractères sont en majuscules, convertissez-les en minuscule en ajoutant 32 à leur valeur ASCII.
            lettre = lettre +32;
        }
        if(r->alphabet[i] - ' ' == 0){ // si nous sommes sur un espace
            j = 26; // alors j passe au suivant
        }
        else {
            j = 'a' - lettre; //sinon on récupère la lettre actuel
        }
        if (isRegionEmpty(r->alphabet[j])) { //si notre region est vide
            return false; //on return false car le mot n'est pas la
        }
        r = r-> alphabet[j];
    }
    return r -> nbBorn; //on return isRegion(r), qui est un bool et qui nous dira alors si la région est présente ou non
}

unsigned int numberOfRegion(struct Region* r){ // donne le nombre de region enregister
    unsigned int count = 0; // on initialise un compteur
    if(r->end){ //si nous sommes à la fin d'un mot
        count ++;
    }
    for(int i = 0; i<27; i++){ //boucle for qui parcourt notre alphabet(+l'espace)
        if(r->alphabet[i] != NULL){ //si l'alphabet != NULL alors
            count += numberOfRegion((r->alphabet[i])); //count augmente
        }
    }
    return count; // on return compteur
}

// Fonction auxiliaire
void setEndWord(struct Region* r, bool end) {
    r->end = end;
}
