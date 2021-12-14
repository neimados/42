Le projet Push_swap est un projet d’algo simple et efficace : il faut trier. Vous avez à votre disposition un ensemble d’entiers, deux piles, et un ensemble d’instructions pour
manipuler les piles.

 Le jeu est constitué de 2 piles nommées a et b.
 
• Au départ :
◦ a contient un nombre arbitraire d’entiers positifs ou négatifs, sans doublons.
◦ b est vide
• Le but du jeu est de trier a dans l’ordre croissant.
• Pour ce faire, on ne dispose que des opérations suivantes :

sa : swap a - intervertit les 2 premiers éléments au sommet de la pile a. Ne fait
rien s’il n’y en a qu’un ou aucun.

sb : swap b - intervertit les 2 premiers éléments au sommet de la pile b. Ne fait
rien s’il n’y en a qu’un ou aucun.

ss : sa et sb en même temps.

pa : push a - prend le premier élément au sommet de b et le met sur a. Ne fait
rien si b est vide.

pb : push b - prend le premier élément au sommet de a et le met sur b. Ne fait
rien si a est vide.

ra : rotate a - décale d’une position vers le haut tous les élements de la pile a.
Le premier élément devient le dernier.

rb : rotate b - décale d’une position vers le haut tous les élements de la pile b.
Le premier élément devient le dernier.

rr : ra et rb en même temps.

rra : reverse rotate a - décale d’une position vers le bas tous les élements de
la pile a. Le dernier élément devient le premier.

rrb : reverse rotate b - décale d’une position vers le bas tous les élements de
la pile b. Le dernier élément devient le premier.

rrr : rra et rrb en même temps.

BONUS : Réaliser un programme checker qui renverra OK ou KO selon les instructions données par le programme push_swap.

Le nombre de mouvement étant limité, l'utilisation d'un algorithme optimisé est indispensable.
Pour ce projet, je recommande l'utilisation de liste chainée plutôt que de tableau pour éviter au maximum les leaks. 
Je suis donc parti sur un tri manuel pour 3 éléments étant donné qu'il n'y a que 5 possibilités. 
Pour 5, il suffit donc de réutiliser la même fonction après avoir écarté le nombre maximum et minimum de la pile A. L'utilisation de liste doublement chainée est donc intéressante pour optimiser les mouvements de la pile.
Puis, j'ai opté pour un tri par insertion qui consiste à chercher le plus petit nombre et l'écarter jusqu'à que la pile A soit vide (cf. liste doublement chainée). Malheureusement, au dela d'une vingtaine d'éléments, cette solution est totalement inefficace.
Il a donc fallu opter pour un autre algorithme plus optimisé. J'ai opté pour le Radix Sort (tri par base). Afin de le mettre en place, il a d'abord fallu simplifier les nombres car le Radix ne gère pas les nombres négatifs. Pour cela, j'ai donc attribuer un index à chaque nombre, le plus petit devient donc l'index 1 puis l'index 2 ... Enfin, étant donné que nous n'avons que 2 piles à disposition, le Radix a donc du être modifié en base 2. 
Le résultat final est convenable mais ce n'est pas la solution la plus optimisée.
