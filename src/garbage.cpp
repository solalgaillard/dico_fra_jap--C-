/*
Aucune de ces fonctions ne sont utilisés dans le
programme mais elles pourraient être bien utiles
dépendemment des futures transformations apportées
au programme.

*/
#include "dico_jap_fra.h"

/*Vide la mémoire d'une structure Entry de manière
récursive.*/
void garbage_all(entree gc_struct)
{ 
	free(kana(original(gc_struct))) ;
	if (kanji(original(gc_struct)))
		free(kanji(original(gc_struct))) ;
	free(original(gc_struct)) ;
	
	garbage_francais(trad_et_cat(gc_struct)) ; 

	if (cdr(gc_struct))
		garbage_all(cdr(gc_struct)) ;
	
	free(gc_struct);
	return ;
}

/*Appeler pour vider la mémoire de la partie 
  française de la structure*/
void garbage_francais(francais gc_struct)
{ 
	if (gc_struct) { 
		if (categories(gc_struct))
			garbage_doublet(categories(gc_struct)) ;

		if (traductions(gc_struct))
			garbage_doublet(traductions(gc_struct)) ;		
	}
	
	if (cdr(gc_struct))
		garbage_francais(cdr(gc_struct)) ;
	
	free(gc_struct) ;
	return ; 
}


/*Appeler pour effictevement vider la mémoire de la partie 
  française de la structure, c'est-à-dire ses sous doublets.*/
void garbage_doublet(doublet gc_struct) 
{ 
	if (gc_struct)
		free(mot(gc_struct)) ;
	

	if (cdr(gc_struct))
		garbage_doublet(cdr(gc_struct)) ;
	
	free(gc_struct) ;
	return ; 
}
