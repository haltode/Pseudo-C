#ifndef MAIN_H
#define MAIN_H 

/* ----- Vous pouvez utiliser des "clean" dans le code ----- */

#ifdef __WIN32__
#define clean system("cls")

#else
#define clean system("clear")
#endif

/* ----- Lib a inclure ----- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----- Define ----- */

#define TAILLE_MAX 1000
#define TAILLE_LIGNE 10000
#define TAILLE_TAB1 6
#define TAILLE_TAB2 7
#define TAB fprintf(sortie, "    ")
#define INDENTATION for(nbTabulations = 0; nbTabulations < indentation; nbTabulations++)\
					TAB;

/* ----- Enumerations + Structures ----- */

typedef enum {INT, DOUBLE, CHAR, STRING} type;
typedef enum {CONSOLE, FICHIER} flux;

typedef struct {
char *mot;
void (*fonction)(const char *);
}s_syntax;

typedef struct {
char *mot;
void (*fonction)(void);
}s_syntax_particulier;

/* ----- Variables globales ----- */

FILE *sortie = NULL;
FILE *fichierErreur = NULL;
int bug = 0;
int indentation = 1;
int nbTabulations = 0;

/* ----- Prototypes ----- */

void instruction(const char *ligne, int numeroLigne);
void finBoucleFaire(const char *ligne);
void boucleFaire(void);
void bouclePour(const char *ligne);
void boucleTantQue(const char *ligne);
int si(const char *ligne);
int sinonSi(const char *ligne);
int sinon(const char *ligne);
void conditionSinon(void);
void conditionSinonSi(const char *argument);
void conditionSi(const char *argument);
char *remplacerCondition(char condition[]);
void lire(const char *argument);
void afficher(const char *argument);
char lettreType(const char *type);
int affecter(const char *affectation);
void affecterVar(const char *var);
void variable(const char *declaration);
type choixType(const char *valeur);
void initAlea(void);
void effacerEcran(void);
void pauseEcran(const char *ligne);

void debutFichier(void);
void finFichier(void);
void crochetFerme(void);

void aide(void);
FILE *fichier(const char *chemin, const char *mode);
void erreur(const char *s);
void lireEntree(char *s);
void afficherSortie(void);
void afficherErreur(void);

/* ----- Tableau contenant les instructions ----- */

s_syntax commande[TAILLE_TAB1] = 
{
	{"Afficher ", afficher},
	{"Lire ", lire},	
	{"Tant Que ", boucleTantQue},
	{"Pour ", bouclePour},
	{"Pause ", pauseEcran},
	{"Fin Boucle, Tant Que ", finBoucleFaire}
};

s_syntax_particulier instructionsIndisp[TAILLE_TAB2] =
{
	{"Debut", debutFichier},
	{"Init Aleatoire", initAlea},
	{"Effacer", effacerEcran},
	{"Fin", finFichier},
	{"Fin Si", crochetFerme},
	{"Fin Boucle", crochetFerme},
	{"Faire", boucleFaire}
};

#endif

