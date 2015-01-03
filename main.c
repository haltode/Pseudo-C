#include "main.h"

int main(int nbArguments, char *argument[])
{
	flux e_entree, e_sortie;
	FILE *entree;
	char pseudo_code[TAILLE_MAX];
	int ligneActuel;
	
	e_entree = e_sortie = CONSOLE;
	entree = NULL;
	strcpy(pseudo_code, "Pseudo-C");
	
	//clean;

	/* ----- Arguments ----- */
	
	sortie = fichier("sortie.c", "w+");
	fichierErreur = fichier("erreur.txt", "w+");
	
	if(nbArguments > 1)
	{
		if(strcmp(argument[1], "-h") == 0)
		{
			aide();
			return EXIT_SUCCESS;
		}
		else
		{
			if(strcmp(argument[1], "-") != 0)
			{
				e_entree = FICHIER;
				entree = fichier(argument[1], "r");
			}
			if(strcmp(argument[2], "-") != 0)
			{
				e_sortie = FICHIER;
				sortie = fichier(argument[2], "w+");
			}
		}
	}

	/* ----- Lecture du pseudo-code ----- */

	for(ligneActuel = 1; strcmp(pseudo_code, "Fin") != 0; ligneActuel++)
	{
		/* ----- Entree ----- */
		if(e_entree == CONSOLE)
		{
			printf("%d  ", ligneActuel);
			lireEntree(pseudo_code);
		}
		else if(e_entree == FICHIER)
			fscanf(entree, "%[^\n]\n", pseudo_code);
		
		/* ----- Transformation + Sortie ----- */
		
		instruction(pseudo_code, ligneActuel);
	} 
	
	/* ----- Fermeture des fichiers ----- */
	
	if(e_entree == FICHIER)
		fclose(entree);
		
	fclose(sortie);
	fclose(fichierErreur);
	
	/* ----- Gestion des erreurs ----- */
	
	if(e_sortie == CONSOLE && bug == 0) // Pas d'erreur + sortie en console
		afficherSortie();
	else if(bug > 0) // Erreur = afficher les erreurs dans la console
		afficherErreur();
	
	return EXIT_SUCCESS;
}

/* ----- Fonction principale gerant toutes les instructions ----- */

void instruction(const char *ligne, int numeroLigne)
{	
	int i, j;
	int estInstruction;
	
	estInstruction = 0;
	
	/* ----- Cas normaux d'instructions ----- */
	
	if(strcmp(ligne, "Debut") != 0 && strcmp(ligne, "Fin Si") != 0 &&
	   strstr(ligne, "Fin Boucle") == NULL && sinonSi(ligne) == 0 &&
	   sinon(ligne) == 0)
		INDENTATION
	
	for(i = 0; i < TAILLE_TAB1; i++)
	{
		if(strstr(ligne, commande[i].mot) != NULL)
		{
			commande[i].fonction(ligne);
			estInstruction = 1;
		}
	}
	
	for(j = 0; j < TAILLE_TAB2; j++)
	{
		if(strcmp(ligne, instructionsIndisp[j].mot) == 0)
		{
			instructionsIndisp[j].fonction();	
			estInstruction = 1;
		}
	}
	
	/* ----- Cas particuliers d'instructions ----- */
	
	if(strstr(ligne, "<-") != NULL)
	{
		variable(ligne);
		estInstruction = 1;
	}
	else if(affecter(ligne))
	{
		affecterVar(ligne);
		estInstruction = 1;
	}
	else if(si(ligne))
	{
		conditionSi(ligne);
		estInstruction = 1;
	}
	else if(sinonSi(ligne))
	{
		conditionSinonSi(ligne);
		estInstruction = 1;
	}
	else if(sinon(ligne))
	{
		conditionSinon();
		estInstruction = 1;
	}
	
	/* ----- Erreur, l'instruction est invalide ----- */
	
	if(estInstruction == 0)
	{
		fprintf(fichierErreur, "ERREUR [ligne %d] : Instruction invalide !\n", numeroLigne);
		bug++;
	}
}

/* ----- Boucle ----- */

void finBoucleFaire(const char *ligne)
{
	char condition[TAILLE_MAX];
	
	sscanf(ligne, "Fin Boucle, Tant Que %[^\n]\n", condition);
	indentation--;
	INDENTATION
	fprintf(sortie, "} while %s;\n", remplacerCondition(condition));
}

void boucleFaire(void)
{	
	fprintf(sortie, "do\n");
	INDENTATION
	fprintf(sortie, "{\n");
	indentation++;
}

void bouclePour(const char *ligne)
{	
	char condition[TAILLE_MAX];
	int i;
	
	sscanf(ligne, "Pour %[^\n]\n", condition);
	
	for(i = 0; i < strlen(condition); i++)
	{
		if(condition[i] == ',')
			condition[i] = ';';
	}
	
	fprintf(sortie, "for (%s)\n", remplacerCondition(condition));
	INDENTATION
   	fprintf(sortie, "{\n");
   	indentation++;
}

void boucleTantQue(const char *ligne)
{	
	if(ligne[0] == 'T')
	{
		char condition[TAILLE_MAX];
	
		sscanf(ligne, "Tant Que %[^\n]\n", condition);
	
		fprintf(sortie, "while %s\n", remplacerCondition(condition));
		INDENTATION
   		fprintf(sortie, "{\n");
   		indentation++;
	}
}

/* ----- Condition ----- */

int si(const char *ligne)
{	
	if(ligne[0] == 'S' && ligne[1] == 'i' && ligne[2] == ' ')
		return 1;
	else
		return 0;
}

int sinonSi(const char *ligne)
{
	if(sinon(ligne) == 1 && ligne[5] == ' ' && ligne[6] == 'S' && ligne[7] == 'i' && ligne[8] == ' ')
		return 1;
	else
		return 0;
}

int sinon(const char *ligne)
{
	if(ligne[0] == 'S' && ligne[1] == 'i' && ligne[2] == 'n' && ligne[3] == 'o'
	&& ligne[4] == 'n')
		return 1;
	else
		return 0;
}

void conditionSinon(void)
{
	indentation--;
	INDENTATION
	fprintf(sortie, "}\n");
	
	INDENTATION
	fprintf(sortie, "else\n");
	INDENTATION
   	fprintf(sortie, "{\n");
   	indentation++;
}

void conditionSinonSi(const char *argument)
{
	char condition[TAILLE_MAX];
	
	sscanf(argument, "Sinon Si %[^\n]\n", condition);
   	
   	indentation--;
	INDENTATION
   	fprintf(sortie, "}\n");
   	
   	INDENTATION
   	fprintf(sortie, "else if%s\n", remplacerCondition(condition));
   	INDENTATION
   	fprintf(sortie, "{\n");
   	indentation++;
}

void conditionSi(const char *argument)
{
	char condition[TAILLE_MAX];
	
	sscanf(argument, "Si %[^\n]\n", condition);
	
   	fprintf(sortie, "if%s\n", remplacerCondition(condition));
   	INDENTATION
   	fprintf(sortie, "{\n");
   	indentation++;
}

char *remplacerCondition(char condition[])
{
	if(strstr(condition, "ET") != NULL ||
	   strstr(condition, "OU") != NULL)
	{
		int i;
	
		for(i = 0; i < strlen(condition) - 1; i++)
    	{
    		if(condition[i] == 'E' && condition[i + 1] == 'T')
    		    condition[i] = condition[i + 1] = '&';
    		else if(condition[i] == 'O' && condition[i + 1] == 'U')
    	   		condition[i] = condition[i + 1] = '|';
    	}
    }
    
    return condition;		
}

/* ----- Lire + Afficher ----- */

void lire(const char *argument)
{
	char type[50];
	char nom[50];
	char caractere;
	
	sscanf(argument, "Lire %s %s\n", type, nom);
	fprintf(sortie, "scanf(\"%%");
	
	caractere = lettreType(type);
	if(caractere == 'f')
		fprintf(sortie, "lf");
	else if(caractere == 's')
		fprintf(sortie, "[^\\n]");
	else
		fprintf(sortie, "%c", caractere);
		
	if(caractere == 's')
		fprintf(sortie, "\\n\", %s);\n", nom);
	else
		fprintf(sortie, "\\n\", &%s);\n", nom);
}

void afficher(const char *argument)
{
	char arg[TAILLE_MAX * 100];
	
	sscanf(argument, "Afficher %[^\n]\n", arg);
	
	if(arg[0] == '\"')
		fprintf(sortie, "printf(%s);\n", arg);
	else
	{
		char type[50];
		char var[50];
		char caractere;
		sscanf(argument, "Afficher %s %[^\n]\n", type, var);
		
		fprintf(sortie, "printf(\"%%");
		
		caractere = lettreType(type);
			
		fprintf(sortie, "%c\", %s);\n", caractere, var);
	}
}

char lettreType(const char *type)
{
	if(strcmp(type, "entier") == 0)
		return 'd';
	if(strcmp(type, "flottant") == 0)
		return 'f';
	if(strcmp(type, "caract") == 0)
		return 'c';
	if(strcmp(type, "chaine") == 0)
		return 's';
}

/* ----- Affecter + Declarer une variable ----- */

int affecter(const char *affectation)
{
	char nom[50];
	char valeur[TAILLE_MAX];
	
	if(sscanf(affectation, "%s = %[^\n]\n", nom, valeur) == 2)
		return 1;
	else
		return 0;
}

void affecterVar(const char *var)
{
	char nom[50];
	char valeur[TAILLE_MAX];
	
	sscanf(var, "%s = %[^\n]\n",nom, valeur);
	
	if(strstr(valeur, "Aleatoire") != NULL)
	{
		char max[50];
		fprintf(sortie, "%s = ", nom);
		sscanf(valeur, "Aleatoire %[^\n]\n", max);
		
		fprintf(sortie, "rand() %s;\n", max);
	}	
	else if(choixType(valeur) != STRING)
		fprintf(sortie, "%s;\n", var);
	else
		fprintf(sortie, "strcpy(%s, %s);\n", nom, valeur);
}

void variable(const char *declaration)
{
	char nom[50];
	char valeur[TAILLE_MAX];
	type retour;
	
	char *estTableau;
	
	estTableau = strstr(declaration, "Tableau ");
	
	if(estTableau != NULL)
		sscanf(declaration, "Tableau %s <- %[^\n]\n", nom, valeur);
	else
		sscanf(declaration, "%s <- %[^\n]\n", nom, valeur);
	
	retour = choixType(valeur);
	
	switch(retour)
	{
		case INT:
			fprintf(sortie, "int ");
		break;
		case DOUBLE:
			fprintf(sortie, "double ");
		break;
		case CHAR:
			fprintf(sortie, "char ");
		break;
		case STRING:
			fprintf(sortie, "char ");
		break;
	}
	
	if(estTableau != NULL)
	{
		if(retour == STRING)
			fprintf(sortie, "*");
		fprintf(sortie, "%s = {%s};\n", nom, valeur);
	}
	else
	{
		if(retour != STRING)
			fprintf(sortie, "%s = %s;\n", nom, valeur);
		else
			fprintf(sortie, "%s[] = %s;\n", nom, valeur);
	}
}

type choixType(const char valeur[])
{
	if(valeur[0] == '\'')
		return CHAR;
	else if(valeur[0] == '"')
		return STRING;
	else if(strchr(valeur, '.') != NULL)
		return DOUBLE;
	else
		return INT;
}

void initAlea(void)
{
	fprintf(sortie, "srand(time(NULL));\n");
}

void effacerEcran(void)
{
	fprintf(sortie, "system(\"clear\");\n");
}

void pauseEcran(const char *ligne)
{
	int nbSecondes;
	
	sscanf(ligne, "Pause %d\n", &nbSecondes);
	fprintf(sortie, "sleep(%d);\n", nbSecondes);
}

/* ----- Code de base dans le fichier ----- */

void debutFichier(void)
{
	fprintf(sortie, "#include <stdio.h>\n");
	fprintf(sortie, "#include <stdlib.h>\n");
	fprintf(sortie, "#include <string.h>\n");
	fprintf(sortie, "#include <time.h>\n");
	fprintf(sortie, "#include <unistd.h>\n\n");
	fprintf(sortie, "int main(void)\n");
	fprintf(sortie, "{\n");
}

void finFichier(void)
{
	fprintf(sortie, "return 0;\n");
	fprintf(sortie, "}\n\n");
}

/* ----- Affiche un crochet ferme dans le code en sortie (fin d'un bloc) ----- */

void crochetFerme(void)
{
	indentation--;
	INDENTATION
	fprintf(sortie, "}\n");
}

/* ----- Aide ----- */

void aide(void)
{
	char choix;
	
	printf("Le fichier aide contient plus de 150 lignes, voulez-vous l'afficher (o/n)"
	" dans la console ? (vous pouvez le lire en ouvrant le fichier aide.txt)\n");
	scanf("%c", &choix);
	
	if(choix == 'o')
	{
		char ligne[TAILLE_LIGNE];
		FILE *aide;
	
		aide = NULL;
		aide = fichier("aide.txt", "r");

		while(fgets(ligne, TAILLE_LIGNE, aide) != NULL)
			printf("%s", ligne);
		
		fclose(aide);
	}
	else
		printf("Vous pouvez toujours consultez l'aide en ouvrant le fichier aide.txt !\n");
	
}

/* ----- Ouvre un fichier donne en parametre ----- */

FILE *fichier(const char *chemin, const char *mode)
{
	FILE *tmp;
	tmp = NULL;
	
	tmp = fopen(chemin, mode);
	
	if(tmp == NULL)
		erreur("Nom de fichier incorrect");

	return tmp;
}

/* ----- Afficher une erreur dans le main.c (probleme de fichier nottament) ----- */

void erreur(const char *s)
{
	printf("ERREUR : [%s]\n", s);
	exit(EXIT_FAILURE);
}

/* ----- Lire l'entree de maniere securise ----- */

void lireEntree(char *s)
{
	char *position;
	
	position = NULL;
	
	fgets(s, TAILLE_LIGNE, stdin);
	
	position = strchr(s, '\n');
	
	if(position != NULL)
		*position = '\0';
}

/* ----- Affiche le contenu du fichier sortie.c (si l'entree est sur la console) ----- */

void afficherSortie(void)
{
	char ligne[TAILLE_LIGNE];
	
	sortie = fichier("sortie.c", "r");
	printf("\n"); 

	while(fgets(ligne, TAILLE_LIGNE, sortie) != NULL)
		printf("%s", ligne);
		
	fclose(sortie);
}

/* ----- Affiche une erreur dans le fichier erreur.txt ----- */

void afficherErreur(void)
{
	FILE *fichierErreur;
	char ligne[TAILLE_LIGNE];
	
	fichierErreur = fichier("erreur.txt", "r");
	printf("\n"); 

	while(fgets(ligne, TAILLE_LIGNE, fichierErreur) != NULL)
		printf("%s", ligne);
		
	fclose(fichierErreur);
}

