#ifndef _GARBAGE_H_
#define _GARBAGE_H_
/*
Aucune de ces fonctions ne sont utilisés dans le
programme mais elles pourraient être bien utiles
dépendemment des futures transformations apportées
au programme.

*/
#include "dico_jap_fra.h"

/*Fonctions pour libérer la mémoire préalablement assignée.
  Elles sont divisées en trois, une pour chaque niveau,
  ce qui leur permet d'être récursive à leur niveau.*/

/*Nettoie au niveau de la structure Entry et Japanese*/
void garbage_all(entree);

/*Nettoie au niveau de la structure French*/
void garbage_francais(francais);

/*Nettoie au niveau des doublets*/
void garbage_doublet(doublet);
#endif
