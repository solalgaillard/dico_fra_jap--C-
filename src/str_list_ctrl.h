#ifndef _STR_LIST_CTRL_H_
#define _STR_LIST_CTRL_H_
#include "dico_jap_fra.h"

/*Fonctions de manipulations chaînes et de listes*/

/*Prend une chaîne en argument et alloue en
  mémoire l'espace pour une nouvelle chaîne 
  de longueur len construite à partir de
  cette dernière. La chaîne originale
  n'est pas affectée,*/
wstring my_str_trim(wstring ligne, int len);

/*retourne index du caractère, -1 si vide*/
int my_strchr_pos(wchar_t, const wstring);

/*retourne l'index correspondant au début de la 
  première chaîne dans la deuxième si elle y est inclue*/
int my_str_in_str(const wstring, const wstring);

/*compte la longueur d'une chaîne*/
int my_len_str(wstring);

/*compte le nombre d'éléments d'une liste liée*/
int compte_el(francais L);

/*Affecte une entrée au cdr d'une autre
  Non utilisé dans le programme*/
entree push_entree(entree , entree);
#endif
