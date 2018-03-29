#ifndef _TO_STRUCT_H_
#define _TO_STRUCT_H_
#include "dico_jap_fra.h"

/*Fonctions d'acquisations des mots
  afin de les placer dans notre structure.*/

/*Fonction de contrôle qui ouvre
  le fichier du dictionnaire.*/
entree file_to_struc() ;

/*Fonction qui contrôle la division de la ligne
  pour insérer les données dans notre structure.*/
entree line_to_struc(wstring, entree) ;

/*Prend la partie japonaise de la ligne et 
  l'insère dans la structure Japanese*/
japonais to_jap(wstring) ;

/*Prend la partie française de la ligne et 
  l'insère dans la structure French*/
francais to_fra(wstring) ;

/*Subdivise la partie française de la ligne
  en catégories et traductions*/
doublet to_cat(wstring) ;
doublet to_trad(wstring, bool, bool) ;

/*si erreur on sort du programme*/
void usage(wstring) ;

#endif
