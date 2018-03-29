#ifndef _TRADUIT_H_
#define _TRADUIT_H_
#include "dico_jap_fra.h"

/*Fonctions d'accès afin de traduire
  les mots à partir de la structure */

/*fonction principale*/
void traduit(wstring, entree) ;

/*hook prévoyant un interprète à romaji*/
wstring in_romaji(wstring);

/*Sonde la partie de l'index correspondant
  à l'alphabet entré. Régurgite la traduction
  si le mot correspond.*/
int fra_ou_jap(wstring, entree, bool, int idx = 0) ;

/*cherche le mot dans la structure Japanese*/
bool in_jap(japonais, wstring);

/*cherche le mot dans la structure French
  avec une fonction auxiliaire pour cause
  d'appels récursifs*/
bool in_fra(francais, wstring);
bool in_fra_aux(doublet, wstring);


/*Fonctions d'impressions à trois niveaux
  Le niveau général Entry et Japanese 
  et les niveaux récursifs de catégories
  et traductions*/
void print_ent(entree);
void print_francais(francais, bool , int);
void print_doublets(doublet, wstring);
#endif
