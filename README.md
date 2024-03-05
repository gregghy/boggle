# README.md
# (**) Boggle ( )

Écrire en C un programme qui trouve toutes les solutions d'une grille de Boggle (et les imprime).

Les mots authorisés peuvent être stockés dans un fichier texte où chaque ligne contiendra un mot.

Le programme doit prendre en compte le fait qu'au Boggle toutes les lettres sont non accentuées. (E peut correspondre l'un des caractères suivants: EÉÈËÊ)

# charges et plan d'implémentation:
règles du Boggle https://www.boggle.fr/regles.php
fichier de mots https://www.pallier.org/extra/liste.de.mots.francais.frgut.txt
chaque case a entre 3 et 8 voisins
type case:
	1 char (lettre stockée)
	1 boolean (case visitée auparavant?)

1 constante de taille de grille (4 par défaut)
1 tableau ayant une taille

chaque case n'est que visitée si le test case non-visitée passe.
à chaque étape, le mot courant est comparé à la liste de mots qui existent (peut-être triés dans une table de hachage auparavant pour accélérer la recherche).

la grille est commencée par chacune des cases de la grille, puis parcourue recursivement dans toutes les directions disponibles. si avec les lettres de la récursion présente, un mot est trouvé dans la liste de mots (avec les lettres dans le bon ordre), alors un compteur est incrémenté. la fonction arrive au cas d'arrêt lorsqu'aucunes des cases adjacentes sont disponibles.

# exemple:
U R E O 
R O A P
A R V U
T S E E

