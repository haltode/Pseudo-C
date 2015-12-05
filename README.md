# Pseudo-C

*Date du projet : avril 2013*

## Principe

Le Pseudo-C est un **traducteur**/**interpréteur** permettant de transformer du pseudo-code (l'entrée) directement en langage C (la sortie).

Le Pseudo-C permet de traduire des programmes entiers pouvant contenir :

- Des variables (entiers, flottants, caractères, et chaînes de caractères)
- Des tableaux (de n'importe quels types de variables)
- Des appels à des fonctions (pour lire, écrire, etc.)
- Des conditions
- Des boucles
- Des déclarations/affectations

Voici par exemple le fameux programme affichant "Hello World !" en pseudo-code (entrée) :

```nohighlight
Debut
  Afficher "Hello World !\n"
Fin
```

Et voici le fichier en C obtenu (sortie) :

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    printf("Hello World !\n");
    return 0;
}
```

Le Pseudo-C inclut une gestion des erreurs dans l'entrée, ainsi qu'un système de paramètre permettant de choisir le mode de l'entrée et le mode de sortie (depuis un fichier ou directement dans la console).

## Compilation/Exécution

Pour utiliser le Pseudo-C vous devez compiler le fichier main.c, puis l'exécuter.

Pour cela placez-vous dans le dossier Pseudo-C et effectuez cette commande :

```bash
gcc main.c -o main
```

Puis :

```bash
./main
```

## Argument

Vous pouvez donner des arguments en entrée du programme pour définir par exemple l'entrée et la sortie :

```bash
./main [ENTREE] [SORTIE]
```

Où `ENTREE` est le fichier d'entrée (ou un `-` si l'entrée se fait dans la console), et `SORTIE` le fichier de sortie (ou `-` pour une sortie directement dans la console).

Pour afficher l'aide :

```bash
./main -h
```

## Syntaxe et instruction

Dans le Pseudo-C, il y a plusieurs instructions que vous pouvez utiliser, et une syntaxe à respecter.

### Déclaration et initialisation d'une variable

```
nom_variable <- valeur_initiale
```

Le type de la variable est automatiquement défini en fonction de `valeur_initiale`.

### Affecter une valeur à une variable

```
nom_variable = nouvelle_valeur
```

### Afficher du texte ou une variable

```
Afficher "texte"
```

Pour afficher une variable, indiquez le type et le nom de la variable à la place du texte :

```
Afficher type_variable nom_variable
```

### Lire depuis l'entrée

```
Lire type_variable nom_variable
```

### Condition

```
Si (condition)
	INSTRUCTIONS
```

```
Sinon Si (condition)
	INSTRUCTIONS
```

```
Sinon
	INSTRUCTIONS
```

A la fin de chaque bloc de condition, vous devez y mettre un `Fin Si` :

```
Si (condition1)
	Instruction 1
Sinon Si (condition2)
	Instruction 2
Sinon
	Instruction 3
Fin Si
```

### Boucle

```
Tant Que (condition)
	INSTRUCTIONS
Fin Boucle
```

```
Pour initialisation, condition, incrémentation
	INSTRUCTIONS
Fin Boucle
```

```
Faire
	INSTRUCTIONS
Fin Boucle, Tant Que (condition)
```

### Tableau

```
Tableau nom_tableau[taille_tableau] <- valeur_initiale
```

Pour utiliser un tableau :

```
nom_tableau[index]
```

Par exemple pour afficher un élément `i` du tableau :

```
Afficher entier tableau[i]
```

### Autres

#### Aléatoire

Pour utiliser un système générant des nombres pseudo-aleatoires, il faut premièrement initialiser le générateur à l'aide de cette commande :

```
Init Aleatoire
```

Puis vous pouvez utiliser la fonction `Aleatoire` comme ceci :

```
entier = Aleatoire
```

#### Pause

Vous pouvez effectuer une pause dans votre programme en appelant la fonction `Pause` et en précisant le nombre de secondes durant lequel le programme va devoir attendre :

```
Pause 3
```

#### Effacer l'écran

```
Effacer
```
