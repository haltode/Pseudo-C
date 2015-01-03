# Pseudo-C


## Compilation/Exécution

Pour utiliser le Pseudo-c vous devez compiler le fichier main.c, puis l'exécuter.

Pour cela placez vous dans le dossier Pseudo-C et effectuez cette commande :

```bash
gcc main.c -o main
```

Puis :

```bash
./main
```

## Argument

Vous pouvez donner des arguments en entrée du programme pour définir par exemple l'entrée et la sortie, mais aussi pour consulter l'aide.

Si vous ne précisez aucun argument, l'entrée se fera sur la console elle même, ainsi que la sortie.

Vous pouvez préciser le fichier d'entrée et/ou de sortie pour cela il suffit de taper la commande pour compiler/exécuter le fichier, puis de rajouter à la fin le nom de votre fichier d'entrée et le nom de votre fichier de sortie. Vous pouvez aussi indiquer un seul des deux fichiers, dans ce cas-là il faut écrire un '-' pour le fichier non indiqué.

Si vous tapez en argument seulement -h, cela vous mènera à l'aide.

### Exemple

```bash
gcc -o main.x main.c ; ./main.x -h
```
-> Cette commande vous permet de consulter l'aide.

```bash
gcc -o main.x main.c ; ./main.x entree.txt sortie.txt
```
-> Cette commande vous permet de définir l'entrée du programme par le fichier entree.txt, et la sortie sortie.txt. Cela signifie que le code source se trouve dans le fichier entree.txt et le code en langage C se trouvera dans le fichier sortie.txt.

```bash
gcc -o main.x main.c ; ./main.x entree.txt -
```
-> Cette commande vous permet de définir l'entrée du programme par le fichier entree.txt puis de laisser la sortie sur la console.

```bash
gcc -o main.x main.c ; ./main.x - sortie.txt
```
-> Cette commande vous permet de définir la sortie du programme par le fichier sortie.txt et de laisser l’entrée sur la console.

```bash
gcc -o main.x main.c ; ./main.x
```
-> Cette commande vous permet de compiler/exécuter le programme et de laisser l'entrée et la sortie en valeur par défaut (la console).

## Syntaxe et instruction

Dans le Pseudo-C, il y a plusieurs instructions que vous pouvez utiliser, et une syntaxe à respecter.

### Déclaration et initialisation d'une variable

Pour déclarer une variable, il vous suffit de suivre cette syntaxe :

```
nom_variable <- valeur_initiale
```

Où "nom_variable" et "valeur_initiale" sont remplacés par le nom de la variable et par sa valeur d'initialisation. Si vous souhaitez déclarer un entier, il vous suffit de mettre un nombre entier comme valeur. Si vous souhaitez déclarer un flottant, il vous suffit de mettre un nombre flottant avec un '.' à la place de la virgule. Si vous souhaitez déclarer un caractère, il vous suffit de mettre un caractère entre apostrophe. Si vous souhaitez déclarer une chaîne de caractère, il vous suffit de mettre la chaîne de caractère entre guillemet.

### Affecter une valeur à une variable

Pour cela, vous devez respecter la syntaxe suivante :

```
nom_variable = nouvelle_valeur
```

Où "nom_variable" et "nouvelle_valeur" sont remplacés par le nom et la nouvelle valeur de la variable. Les règles pour initialiser une variable sont les mêmes que celles pour lui affecter une valeur.

### Afficher du texte ou une variable

Pour afficher du texte, il faut respecter la syntaxe :

```
Afficher "texte"
```

Où "texte" est le texte que vous souhaitez afficher.

Pour afficher une variable, il faut respecter la syntaxe :

```
Afficher type_variable nom_variable
```

Où "type_variable" et "nom_variable" sont remplacés par le type de la variable à afficher, et le nom de la variable.

### Lire depuis l'entrée

Pour lire depuis l'entrée il faut respecter la syntaxe :

```
Lire type_variable nom_variable
```

Où "type_variable" et "nom_variable" sont remplacés par le type de la variable dans laquelle l'entrée va être lu, et le nom de la variable.

### Condition

Pour effectuer une condition (un test), il faut respecter la syntaxe :

```
Si (condition)
	INSTRUCTIONS
```

Où "condition" et "INSTRUCTIONS" sont remplacés par la condition à respecter pour entrer dans le bloc `Si`, et les instructions à réaliser dans le bloc `Si`.

Il existe aussi :

```
Sinon Si (condition)
	INSTRUCTIONS
```

Et :

```
Sinon
	INSTRUCTIONS
```

A la fin de chaque "bloc" de condition, vous devez y mettre un `Fin Si` :

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

Pour effectuer une boucle, il faut respecter la syntaxe :

```
Tant Que (condition)
	INSTRUCTIONS
Fin Boucle
```

Où "condition" et "INSTRUCTIONS" sont remplacés par la condition à respecter pour entrer dans le bloc `Tant Que`, et les instructions à réaliser dans le bloc `Tant Que`.

Il existe aussi :

```
Pour initialisation, condition, incrémentation
	INSTRUCTIONS
Fin Boucle
```

Où "initialisation", "condition", "incrémentation" et "INSTRUCTIONS" sont remplacés par l'initialisation d'une variable, la condition à respecter pour entrer dans le bloc `Pour`, l'incrémentation de la variable, et les instructions à réaliser dans le bloc `Pour`.

Et aussi :

```
Faire
	INSTRUCTIONS
Fin Boucle, Tant Que (condition)
```

Où "condition" et "INSTRUCTIONS" sont remplacés par la condition à respecter pour entrer dans le bloc `Faire`, et les instructions à réaliser dans le bloc `Faire`. Cette boucle parcourt au moins une fois les INSTRUCTIONS.

### Tableau

Vous pouvez déclarer un tableau grâce à la syntaxe suivante :

```
Tableau nom_tableau[taille_tableau] <- valeur_initiale
```

Où "nom_tableau", "taille_tableau" et "valeur_initiale" sont remplacés par le nom du tableau, sa taille et ses différentes valeurs initiales qui doivent être du même type.

Pour utiliser un tableau il faut utiliser la syntaxe suivante :

```
nom_tableau[index]
```

Où "nom_tableau" et "index" sont remplacés par le nom du tableau et l'index de l'élément de ce tableau auquel on veut accéder.

Par exemple pour afficher l'élément `i` du tableau `boucle` :

```
Afficher entier boucle[i]
```

Ici le tableau boucle est un tableau contenant des entiers.

### Autres

#### Aléatoire

Pour utiliser un système générant des nombres pseudo-aleatoires, il faut premièrement initialiser le générateur à l'aide de cette commande :

```
Init Aleatoire
```

Puis vous pouvez utiliser la fonction `Aleatoire` comme ceci par exemple :

```
entier = Aleatoire
```

Vous ne pouvez pas déclarer une variable contenant directement un nombre 
aléatoire, je m'explique, vous ne pouvez pas faire ceci :

```
variable <- Aleatoire
```

Vous devez déclarer la variable puis lui affecter la valeur que vous souhaitez.

#### Pause

Vous pouvez effectuer une pause dans votre programme en appelant la fonction `Pause` et en précisant le nombre de seconde durant lequel le programme va devoir attendre :

```
Pause 3
```

Cette ligne va mettre en pause votre programme pendant 3 secondes.

#### Effacer

Vous pouvez effacer l'écran en appelant la fonction `Effacer` :

```
Effacer
```