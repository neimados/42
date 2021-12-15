PRINTF

• Vous devez recoder la fonction printf de la libc

• Vous ne devez pas gérer de buffer, contrairement au vrai printf

• Vous devez gérer les conversions suivantes : cspdiuxX%

• Votre rendu sera comparé au vrai printf

• Vous devez utiliser la commande ar pour créer votre librairie, l’utilisation de la
commande libtool est interdite

Une petite description des conversions requises :

• %c imprime un seul caractère.

• %s imprime une chaîne de caractères.

• %p L’argument de pointeur void * est imprimé en hexadécimal.

• %d imprime un nombre décimal (base 10).

• %i imprime un entier en base 10.

• %u imprime un nombre décimal non signé (base 10).

• %x imprime un nombre en hexadécimal (base 16).

• %% imprime un signe de pourcentage..

La difficulté du projet réside dans ses bonus qui étaient la gestion des flags ". - + # 0 space". Pour ce faire, lors du parsing, il a donc fallu prendre en compte ces flags pour les réutiliser lors de l'impression. J'ai opté pour une structure afin de stocker les flags et ainsi les gérer individuellement.
