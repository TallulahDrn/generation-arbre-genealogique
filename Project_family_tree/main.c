#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "together.h"
#include "region.h"
#include "person.h"
#include "familyTree.h"
#include "export.h"

int main(){ // Il faut lire le fichier et savoir comment on recupère les donnees pour finir nos operation de base
    unsigned int choice;
    char* fichier;
    bool welcome = true;
    bool whatDoYou1 = true;
    bool whatDoYou2 = true;
    bool choiceFic = true;
    struct timespec startChrono, endChrono;
    unsigned int elapsedTime;

    while (welcome) {
        printf("WELCOME TO THE FAMILY TREE PROJECT!!!\n\n");
        printf("What do you want to do?\n");
        printf("--------------------------\n");
        printf("1. Read CSV file\n");
        printf("2. Exit\n");
        printf("--------------------------\n");
        printf("Your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Read CSV file
//---------------------- ouverture du fichier CSV ----------------------
                printf("Read CSV file\n");
                printf("--------------------------\n");
                printf("1. little\n");
                printf("2. big\n");
                printf("--------------------------\n");
                printf("Your choice:");
                scanf("%d", &choice);

//---------------------- choix du fichier CSV --------------------------
                FILE *fic;
                choiceFic = true;
                while (choiceFic) {
                    switch (choice) {
                        case 1: { // little
                            fic = fopen("../resources/bd_petite.csv", "rt");
                            choiceFic = false;
                            break;
                        }
                        case 2: { // big
                            fic = fopen("../resources/bd_grande.csv", "rt");
                            choiceFic = false;
                            break;
                        }
                        default: {
                            choiceFic = true;
                        }
                    }
                }
                if (fic == NULL) {
                    printf("L'ouverture du fichier est impossible");
                    exit(0);
                }

//---------------------- lecture du fichier CSV ----------------------
// On cree toute les variables que nous utiliserons pour recupere les variables contenu dans le csv
                clock_gettime(CLOCK_REALTIME, &startChrono);//récupère l'heure exacte de début
                struct Together *t = createTogether();
                unsigned int idPerson;
                unsigned int idFather;
                unsigned int idMother;
                char ligne[80];
                char *name;
                char *firstName;
                char *birth;
                char *region;
                fgets(ligne, 80, fic);

// On lit le fichier jusqu'a la fin
                while (fgets(ligne, 80, fic) != NULL) {
                    idPerson = atoi(strtok(ligne,",")); // la fonction strtok permet de recupere une chaine de caractère et de renvoyer la chaine jusqu'au separateur rentre en paramètre
                    idFather = atoi(strtok(NULL, ",")); // grace au atoi on transforme une chaine de caractère en int
                    idMother = atoi(strtok(NULL, ","));
                    name = strtok(NULL, ",");
                    firstName = strtok(NULL, ",");
                    birth = strtok(NULL, ",");
                    region = strtok(NULL, ",");
                    strtok(NULL, ","); // Non indispensable
                    struct Person *interPerson = createPerson(idPerson, idFather, idMother, name, firstName, birth,region); // on cree une personne
                    struct FamilyTree *interFamily = createFamilyTree(interPerson); // cree la famille de la personne sans cree l'arbre
                    addFirst(t, interFamily);// forme la liste chainee
                    if(idPerson != 0) {
                        insertRegion(t->alphabet, region);
                    }
                }
                fclose(fic);

                addLienFamily(t);

                clock_gettime(CLOCK_REALTIME, &endChrono);//récupère l'heure exacte de fin
                //récupère le temps écoulé en secondes et en nanosecondes et convertit en millisecondes
                elapsedTime = (endChrono.tv_sec - startChrono.tv_sec)*1000 + (endChrono.tv_nsec - startChrono.tv_nsec)/1000000;
                printf("Temps de lecture des fichiers CSV : \n");
                convertIntoMinSec(elapsedTime);

                printf("File read succesfully!\n\n");
                whatDoYou1 = true;

//---------------------- choix de l'exportation ou du travail sur console ----------------------

                while (whatDoYou1) {
                    printf("What do you want to do?\n");
                    printf("--------------------------\n");
                    printf("1. Show family tree info\n");
                    printf("2. Export HTML family tree files\n");
                    printf("3. Export HTML info files\n");
                    printf("4. Export all files\n");
                    printf("5. Query family tree\n");
                    printf("6. Go back to principal menu\n");
                    printf("--------------------------\n");
                    printf("Your choice:");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: { // Show family tree info
                            printf("There are %d people in the data base",t -> size);
                            break;
                        }
                        case 2: { // Export HTML family tree files
                            clock_gettime(CLOCK_REALTIME, &startChrono);//récupère l'heure exacte de début
                            struct FamilyTree* p = t -> head;
                            for(int i = (t -> size)-1; i >= 0; i--) {
                                createHTML(i,p);
                                p = p -> next;
                            }
                            generateFilesList(t -> size); //------------------
                            clock_gettime(CLOCK_REALTIME, &endChrono);//récupère l'heure exacte de fin
                            //récupère le temps écoulé en secondes et en nanosecondes et convertit en millisecondes
                            elapsedTime = (endChrono.tv_sec - startChrono.tv_sec)*1000 + (endChrono.tv_nsec - startChrono.tv_nsec)/1000000;
                            printf("Temps d'exportation des fichiers HTML des arbres : \n");
                            convertIntoMinSec(elapsedTime);
                            printf("HTMl files succesfully exported !\n\n");
                            return 0;
                        }
                        case 3: { // Export HTML info files
                            clock_gettime(CLOCK_REALTIME, &startChrono);
                            createAccueil(t -> size);
                            clock_gettime(CLOCK_REALTIME, &endChrono);//récupère l'heure exacte de fin
                            //récupère le temps écoulé en secondes et en nanosecondes et convertit en millisecondes
                            elapsedTime = (endChrono.tv_sec - startChrono.tv_sec)*1000 + (endChrono.tv_nsec - startChrono.tv_nsec)/1000000;
                            printf("Temps d'exportation du fichier HTML accueil : \n");
                            convertIntoMinSec(elapsedTime);
                            printf("HTMl files Home succesfully exported !\n\n");
                            return 0;
                        }
                        case 4: { // Export all files
                            clock_gettime(CLOCK_REALTIME, &startChrono);//récupère l'heure exacte de début

                            struct FamilyTree* p = t -> head;
                            for(int i = (t -> size)-1; i >= 0; i--) {
                                createHTML(i,p);
                                p = p -> next;
                            }
                            generateFilesList(t -> size); //------------------
                            createAccueil(t -> size);
                            clock_gettime(CLOCK_REALTIME, &endChrono);//récupère l'heure exacte de fin
                            //récupère le temps écoulé en secondes et en nanosecondes et convertit en millisecondes
                            elapsedTime = (endChrono.tv_sec - startChrono.tv_sec)*1000 + (endChrono.tv_nsec - startChrono.tv_nsec)/1000000;
                            printf("Temps d'exportation de tous les fichiers HTML : \n");
                            convertIntoMinSec(elapsedTime);
                            printf("all HTML files succesfully exported !!\n\n");
                            return 0;
                        }
                        case 5: { // Query family tree

//---------------------- choix des petite fonction implementer ----------------------

                            whatDoYou2 = true;
                            while (whatDoYou2) {
                                printf("Query the family tree!\n");
                                printf("--------------------------\n");
                                printf("1. Get first born in the tree\n");
                                printf("2. Get last born in the tree\n");
                                printf("3. Get number of people born in a region\n");
                                printf("4. Get the region with highest number of births\n");
                                printf("5. Get number of people born in a given day and month\n");
                                printf("6. Go back to previous menu\n");
                                printf("--------------------------\n");
                                printf("Your choice:");
                                scanf("%d", &choice);

                                switch (choice) {
                                    case 1:{ // Get first born in the tree
                                        printPerson(getYoungest(t));
                                        break;
                                    }
                                    case 2:{ // Get last born in the tree
                                        printPerson(getOldest(t));
                                        break;
                                    }
                                    case 3:{ // Get number of people born in a region
                                        printf("Which region do you want?\n");
                                        printf("--------------------------\n");
                                        printf("Your choice:");
                                        scanf("%s",region);
                                        if(findRegion(t -> alphabet, region) != 0){
                                            printf("There is %d people born in %s\n",findRegion(t -> alphabet,region),region);
                                        }
                                        else{
                                            printf("The region does not exist !\n");
                                        }
                                        break;
                                    }
                                    case 4:{ // Get the region with highest number of births
                                        printf("%s",getMostBornRegion(t));
                                        break;
                                    }
                                    case 5:{ // Get number of people born in a given day and month
                                        unsigned int day = 0;
                                        unsigned int month = 0;
                                        printf("The day of birth:");
                                        scanf("%d",&day);
                                        printf("The month of birth:");
                                        scanf("%d",&month);
                                        printf("The %d/%d",day,month);
                                        day--;
                                        month++;
                                        printf(" %d born",getNbPersonYear(t,day,month));
                                        break;
                                    }
                                    case 6:{ // Go back to previous menu
                                        whatDoYou2 = false;
                                        break;
                                    }
                                    default:{
                                        whatDoYou2 = true;
                                    }
                                }
                            }
                            break;
                        }
                        case 6: { // Go back to principal menu
                            deleteTogether(t);
                            whatDoYou1 = false;
                            break;
                        }
                        default:{
                            whatDoYou1 = true;
                        }
                    }
                }
                break;
            }
            case 2: { // Exit
                welcome = false;
                break;
            }
            default:{
                welcome = true;
            }
        }
    }
    return 0;
}