#include "str_list_ctrl.h"

/*Retourne une chaîne prise de la précédente et découpée
  dont on a alloué une place en mémoire.
  Ne pas oublier de libérer la chaîne quand on en a plus
  besoin.*/
wstring my_str_trim(wstring ligne, int len)
{
	wstring buf = (wstring)malloc(len * sizeof(wchar_t));
	if (!buf)
		perror("malloc");
	wmemset(buf, NULLCHAR, len) ;
	wcsncpy(buf, ligne, (len - 1)) ;
	return buf ;
}

/*retourne index du caractère dans la 
  chaîne, -1 si vide*/
int my_strchr_pos(wchar_t C, const wstring S)
{ 
	int it = 0;
	while (C neql *(S+it)) { 
		it++ ;
		if (*(S+it) eql NULLCHAR) 
			return -1 ; 
	}
	
	return it ; 
}

/*si la chaîne S1 est présente dans S2, retourne
  l'index de son début dans S2*/
int my_str_in_str(const wstring S1, const wstring S2)
{ 
	int it1 = 0;
	int it2 = 0;
	while (*(S2+it2) neql NULLCHAR) { 
		while (*(S1+it1) eql *(S2+(it1 + it2))) { 
			it1++ ;
      		  	if (*(S1+it1) eql NULLCHAR) 
      		  		return it2 ; 
		}
		it2++ ;
		it1 = 0; 
	}
	return -1 ; 
}
      
/*calcule la longueur d'une chaîne*/
int my_len_str(wstring S)
{
	if (*S) 
		return 1 + my_len_str(S + 1) ;
   	return 0 ; 
}

/*compte le nombre d'éléments dans une liste liée*/
int compte_el(francais L)
{
	if (L) 
		return 1 + compte_el(L->cdr) ;
   	return 0 ;
}


/*pas utilisé*/
/*permet d'affecter une nouvelle entrée à notre liste liée*/
entree push_entree(entree new_ent, entree old_ent)
{ 
	entree ent = (entree)malloc(sizeof(struct Entry)) ;
	if (!ent)
		perror("malloc");
		
	original(ent) = original(new_ent);
	trad_et_cat(ent) = trad_et_cat(new_ent);
	cdr(ent) = old_ent;
	return ent ; 
}
