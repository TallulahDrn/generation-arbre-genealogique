#include <stdlib.h>
#include <stdio.h>
#include "export.h"
#include "Together.h"
#define MAX_PATH_LENGTH 30

//-------------------------------------------------
void generateFilesList(int numberOfFiles) {
    FILE *f = fopen("../export/filesList.js", "w");
    if (f == NULL) {
        printf("Error opening filesList.js!\n");
        return;
    }

    fprintf(f, "const familyPages = [\n");
    fprintf(f, "    \"Accueil.html\"");
    fprintf(f, ",");
    fprintf(f, "\n");
    for (int i = 0; i < numberOfFiles; i++) {
        fprintf(f, "    \"%d.html\"", i);
        if (i < numberOfFiles) {
            fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fprintf(f, "];\n");

    fclose(f);
}
//----------------------------------------



//Fonction qui permet de générer un fichier html par personne
void createHTML(int fileIndex, struct FamilyTree* p) {
    char nameFile[MAX_PATH_LENGTH];
    char* directory = "..";
    char* filePrefix = "export";

    // Construire le chemin complet du fichier
    snprintf(nameFile, MAX_PATH_LENGTH, "%s/%s/%d.html", directory, filePrefix, fileIndex);

    FILE* fp;
    fp = fopen(nameFile,"w");
    if(fp == NULL){
        printf("Error in opening file");
        return;
    }
    //Première branche
    struct Person* child = getChild(p);
    //Deuxième branche
    struct Person* dad = getFather(p);
    struct Person* mom = getMother(p);
    //Troisième branche
    //Père
    struct Person* dGDad = getFatherOfFather(p);
    struct Person* dGMom = getMotherOfFather(p);
    // Mère
    struct Person* mGDad = getFatherOfMother(p);
    struct Person* mGMom = getMotherOfMother(p);

    fprintf(fp,"<!DOCTYPE html>"); // ok
    fprintf(fp,"<html lang=\"fr\">"); // ok
    fprintf(fp, "<head>"); // ok
    fprintf(fp, "<meta charset=\"UTF-8\">"); // ok
    fprintf(fp, "<title>Family Tree</title>"); // ok
    fprintf(fp, "<link rel=\"stylesheet\" href=\"../resources/style.css\">"); // ok
    fprintf(fp, "<script src=\"../resources/script.js\" defer></script>");
    fprintf(fp, "<script src=\"../export/filesList.js\" defer></script>"); //enlever
    fprintf(fp, "</head>"); // ok
    fprintf(fp, "<body>"); // ok
    fprintf(fp, "<div class=\"header\">"); // ok
    fprintf(fp, "<div class=\"back-button-container\">"); // ok
    fprintf(fp, "<button class=\"back-button\" onclick=\"backBoutton()\">←</button>"); // ok
    fprintf(fp, "<span class=\"mini-game-text\">Mini-jeu</span>"); // ok
    fprintf(fp, "</div>"); // ce /div ferme le 'div class="back-button-container"' // ok
    fprintf(fp, "<button class=\"help-button\" onclick=\"hasard()\">?</button>"); // ok
    fprintf(fp, "</div>"); // ce /div ferme le header //ok
    fprintf(fp, "<div class=\"tree\">"); //ok
    fprintf(fp, "<div class=\"node parent\">"); // ok
    // Première branche
    fprintf(fp, "<img src=\"../resources/image/babyIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(child)); // Ne change jamais, car on affichera forcément une personne qui existe // ok
    fprintf(fp, "<div class=\"info-Enfant\"> <span id=\"nom\">%s</span> / <span id=\"prenom\">%s</span> <br><span id=\"birthday\">%s</span> <br><span id=\"region\">%s</span></div>", getName(child), getFirstName(child), getBirth(child), getRegion(child)); // ok
    //Fin première branche
    fprintf(fp, "</div>"); // /div ferme le <div class="node parent"> // ok
    fprintf(fp, "<div class=\"line parent-line\"></div>"); //ok
    fprintf(fp, "<div class=\"row children\">"); //ok
    fprintf(fp, "<div class=\"node child\">"); //ok
    //Deuxième branche
    if(getId(dad) != 0) { // si le père est connu :
        fprintf(fp, "<img src=\"../resources/image/fatherIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(dad)); //ok
        fprintf(fp, "<div class=\"info-Pere\"> <span id=\"nomP\">%s</span>  / <span id=\"prenomP\">%s</span> <br><span id=\"birthdayP\">%s</span> <br><span id=\"regionP\">%s</span></div>", getName(dad), getFirstName(dad),getBirth(dad),getRegion(dad));
    } else{ // si le père est inconnu
        fprintf(fp, "<img src=\"../resources/image/unknowPersonIcon.png\" alt=\"ERROR\">"); //ok
        fprintf(fp, "<div class=\"info-Inconnu\"><span id=\"nomP\">inconnu</span>  / <span id=\"prenomP\">inconnu</span> <br><span id=\"birthdayP\">inconnu</span> <br><span id=\"regionP\">inconnu</span></div>");
    }

    fprintf(fp, "</div>"); // ce /div ferme <div class="node child"> // ok
    fprintf(fp, "<div class=\"line\"></div>"); // ok
    fprintf(fp, "<div class=\"node child\">"); // ok

    if(getId(mom) != 0) { // si le mère est connu :
        fprintf(fp, "<img src=\"../resources/image/motherIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(mom));
        fprintf(fp, "<div class=\"info-Mere\"> <span id=\"nomM\">%s</span>  / <span id=\"prenomM\">%s</span> <br><span id=\"birthdayM\">%s</span> <br><span id=\"regionM\">%s</span></div>", getName(mom), getFirstName(mom),getBirth(mom),getRegion(mom)); // ok
    } else{ // si le mère est inconnu
        fprintf(fp, "<img src=\"../resources/image/unknowPersonIcon.png\" alt=\"ERROR\">"); // ok
        fprintf(fp, "<div class=\"info-Inconnu\"><span id=\"nomM\">inconnu</span>  / <span id=\"prenomM\">inconnu</span> <br><span id=\"birthdayM\">inconnu</span> <br><span id=\"regionM\">inconnu</span></div>");
    }
    //Fin deuxième branche
    fprintf(fp, "</div>"); // ce </div> ferme <div class="node child"> //ok
    fprintf(fp, "</div>"); // ce </div> ferme <div class="row children"> //ok
    fprintf(fp, "<div class=\"row grandchildren\">"); //ok
    fprintf(fp, "<div class=\"node grandchild\">"); //ok
    //Troisième branche
    if(getId(dGDad) != 0) { // si le  père du père est connu :
        fprintf(fp, "<img src=\"../resources/image/grandFatherIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(dGDad));
        fprintf(fp, "<div class=\"info-GPP\"> <span id=\"nomGPP\">%s</span>  / <span id=\"prenomGPP\">%s</span> <br><span id=\"birthdayGPP\">%s</span> <br><span id=\"regionGPP\">%s</span></div>", getName(dGDad), getFirstName(dGDad),getBirth(dGDad),getRegion(dGDad)); //ok
    } else{ // si le père du père est inconnu
        fprintf(fp, "<img src=\"../resources/image/unknowPersonIcon.png\" alt=\"ERROR\">");
        fprintf(fp, "<div class=\"info-Inconnu\"><span id=\"nomGPP\">inconnu</span>  / <span id=\"prenomGPP\">inconnu</span> <br><span id=\"birthdayGPP\">inconnu</span> <br><span id=\"regionGPP\">inconnu</span></div>");
    }

    fprintf(fp, "</div>"); // ce </div> ferme <div class="node grandchild"> //ok
    fprintf(fp, "<div class=\"node grandchild\">"); //ok

    if(getId(dGMom) != 0) { // si le  mère du père est connu :
        fprintf(fp, "<img src=\"../resources/image/grandMotherIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(dGMom)); // ok
        fprintf(fp, "<div class=\"info-GMP\"> <span id=\"nomGMP\">%s</span>  / <span id=\"prenomGMP\">%s</span> <br><span id=\"birthdayGMP\">%s</span> <br><span id=\"regionGMP\">%s</span></div>", getName(dGMom), getFirstName(dGMom),getBirth(dGMom),getRegion(dGMom)); //ok
    } else{ // si le mère du père est inconnu
        fprintf(fp, "<img src=\"../resources/image/unknowPersonIcon.png\" alt=\"ERROR\">"); // ok
        fprintf(fp, "<div class=\"info-Inconnu\"><span id=\"nomGMP\">inconnu</span>  / <span id=\"prenomGMP\">inconnu</span> <br><span id=\"birthdayGMP\">inconnu</span> <br><span id=\"regionGMP\">inconnu</span></div>");
    }


    fprintf(fp, "</div>"); // ce </div> ferme <div class="node grandchild"> // ok
    fprintf(fp, "<div class=\"node grandchild\">"); // ok


    if(getId(mGDad) != 0) { // si le  père de la mère est connu :
        fprintf(fp, "<img src=\"../resources/image/grandFatherIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(mGDad)); // ok
        fprintf(fp, "<div class=\"info-GPM\"> <span id=\"nomGPM\">%s</span>  / <span id=\"prenomGPM\">%s</span> <br><span id=\"birthdayGPM\">%s</span> <br><span id=\"regionGPM\">%s</span></div>", getName(mGDad), getFirstName(mGDad),getBirth(mGDad),getRegion(mGDad));
    } else{ // si le père de la mère est inconnu
        fprintf(fp, "<img src=\"../resources/image/unknowPersonIcon.png\" alt=\"ERROR\">"); // ok
        fprintf(fp, "<div class=\"info-Inconnu\"><span id=\"nomGPM\">inconnu</span>  / <span id=\"prenomGPM\">inconnu</span> <br><span id=\"birthdayGPM\">inconnu</span> <br><span id=\"regionGPM\">inconnu</span></div>");
    }


    fprintf(fp, "</div>"); // ce </div> ferme <div class="node grandchild"> //ok
    fprintf(fp, "<div class=\"node grandchild\">"); //ok
    fprintf(fp, "<div class=\"node grandchild\">"); // ok


    if(getId(mGMom) != 0) { // si la mère de la mère est connu :
        fprintf(fp, "<img src=\"../resources/image/grandMotherIcon.png\" alt=\"ERROR\" data-id=\"%d\" onclick=\"navigateToPerson(this)\">", getId(mGMom)); // ok
        fprintf(fp, "<div class=\"info-GMM\"> <span id=\"nomGMM\">%s</span>  / <span id=\"prenomGMM\">%s</span> <br><span id=\"birthdayGMM\">%s</span> <br><span id=\"regionGMM\">%s</span></div>", getName(mGMom), getFirstName(mGMom),getBirth(mGMom),getRegion(mGMom)); // ok
    } else{ // si la mère de la mère est inconnu
        fprintf(fp, "<img src=\"../resources/image/unknowPersonIcon.png\" alt=\"ERROR\">"); // ok
        fprintf(fp, "<div class=\"info-Inconnu\"><span id=\"nomGMM\">inconnu</span>  / <span id=\"prenomGMM\">inconnu</span> <br><span id=\"birthdayGMM\">inconnu</span> <br><span id=\"regionGMM\">inconnu</span></div>");
    }
    //Fin troisième branche

    fprintf(fp, "</div>"); // ce /div ferme <div class="node grandchild">
    fprintf(fp, "</div>"); // ce /div ferme <div class="row grandchildren">
    fprintf(fp, "</div>"); // ce /div ferme <div class="tree">
    fprintf(fp, "</div>");
    fprintf(fp, "</body>");
    fprintf(fp, "</html>");

    fclose(fp);

}
//fonction qui permet de générer la page d'accueil
void createAccueil(unsigned int size){
    char* nameFile = "../export/Accueil.html";
    FILE* fa;
    fa = fopen(nameFile,"w");
    if(fa == NULL){
        printf("Error in opening file");
        return;
    }

    fprintf(fa, "<!DOCTYPE html>");
    fprintf(fa, "<html lang=\"fr\">");
    fprintf(fa, "<head>");
    fprintf(fa, "<meta charset=\"utf-8\">");
    fprintf(fa, "<title> ACCUEIL </title>");
    fprintf(fa, "<link href=\"../resources/accueil.css\" rel=\"stylesheet\">");
    fprintf(fa, "</head>");
    fprintf(fa, "<body>");
    fprintf(fa, "<div class=\"header\">");
    fprintf(fa, "<div class=\"back-button-container\">");
    fprintf(fa, "<span class=\"mini-game-text\">Bienvenu sur la page d'accueil !</span>");
    fprintf(fa, "<span class=\"mini-game-text\">Retrouvez sur cette page les informations importantes.</span>");
    fprintf(fa, "<span class=\"mini-game-text\">Pour générer une famille au hasard, cliquez sur le bouton '?' juste ici  <span class=\"back-button\">→</span> </span>");
    fprintf(fa, "</div>"); // ce /div ferme le div back-button-container
    fprintf(fa, "<button class=\"help-button\">?</button>");
    fprintf(fa, "</div>"); // ce /div ferme le header
    fprintf(fa, "<div class=\"chart-container\">");
    fprintf(fa, "<div class=\"bar\" data-value=\"100\">"); //MODIFIER
    fprintf(fa, "<div class=\"bar-fill\"></div>");
    fprintf(fa, "<div class=\"bar-label\">Le nombre de personnes en total</div>");
    fprintf(fa, "</div>"); // ce/div ferme la première bar
    fprintf(fa, "<div class=\"bar\" data-value=\"61\">");
    fprintf(fa, "<div class=\"bar-fill\"></div>");
    fprintf(fa, "<div class=\"bar-label\">Le nombre de femmes</div>");
    fprintf(fa, "</div>"); // ce /div ferme la deuxième bar
    fprintf(fa, "<div class=\"bar\" data-value=\"39\">");
    fprintf(fa, "<div class=\"bar-fill\"></div>");
    fprintf(fa, "<div class=\"bar-label\">Le nombre d'hommes</div>");
    fprintf(fa, "</div>"); // ce /div ferme la troisième bar
    fprintf(fa, "<div class=\"bar\" data-value=\"20\">");
    fprintf(fa, "<div class=\"bar-fill\"></div>");
    fprintf(fa, "<div class=\"bar-label\">Le nombre de familles différentes</div>");
    fprintf(fa, "</div>"); // ce /div ferme la quatrième bar
    fprintf(fa, "</div>"); //ce /div ferme la "chart-container"
    fprintf(fa, "<script src=\"../export/filesList.js\"></script>");
    fprintf(fa, "<script src=\"../resources/accueil.js\"></script>");
    fprintf(fa, "</body>");
    fprintf(fa, "</html>");

    fclose(fa);
}



