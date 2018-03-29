#include "traduit.h"
#include "str_list_ctrl.h"
#include "widget.h"

/* =============================================== CLOBALES ==============================================*/

// pour imprimer sur le widget
extern Widget Current_Output ;

/* =============================================== FONCTIONS ==============================================*/


/*fonction principale qui se charge de traduire le mot*/
void traduit(wstring mot, entree dico)
{
	/*Si caractère Latin Extended-A, on traduit vers le jap*/
	bool vers_jap = (*mot < 383) ;
	
	/*compte et imprime occurences*/
	int rslt_count = fra_ou_jap(mot, dico, vers_jap) ;
	
	
	/*En l'absence de résultats :*/
	if (!rslt_count) {
	
		/*Pour se réserver le droit de créer un interprète 
		  à romaji.On relancerait l'itération
		  avec le mot converti en kana*/
	
		wstring romaji ; /*la version romaji entraîne 
		 		   forcément un caractère > 383*/
		if ((romaji = in_romaji(mot)))
			return traduit(romaji, dico) ;
	
		widget_print(Current_Output, (wstring)L"\n\nDésolé mais le dictionnaire n'a trouvé aucun résultat.\n") ;
	}
	
	widget_print(Current_Output, (wstring)L"\ndictionnaire-japonais-francais> ");
	widget_newpos(Current_Output) ;
}


/*hook en vu d'un interprète à romaji*/
wstring in_romaji(wstring mot)
{
	return NULL;
}

/*Regarde dans quelle partie de structure il faut chercher
  et imprime s'il a trouvé dans une de ces parties.*/
int fra_ou_jap(wstring mot, entree ent, bool vers_jap, int idx)
{
	if (!ent)
		return idx ;
	
	if (vers_jap) {
		if (in_fra(trad_et_cat(ent), mot)) {
			print_ent(ent) ;
			return fra_ou_jap(mot, cdr(ent), vers_jap, idx+1) ;
		}
	}
	
	if (in_jap(original(ent), mot)) {
		print_ent(ent) ;
		return fra_ou_jap(mot, cdr(ent), vers_jap, idx+1) ;
	}
	
	return fra_ou_jap(mot, cdr(ent), vers_jap, idx) ;
}

/*regarde si mot présent dans la structure Japanese*/
bool in_jap(japonais jap, wstring mot)
{ 
	if (wcscmp(mot, kana(jap)) eql 0) 
		return true ;
	if (kanji(jap) && wcscmp(mot, kanji(jap)) eql 0) 
		return true ;

	return false ; 
}


/*Tant qu'il y a des cdr de structure French, regarde 
  dans les traductions à la recherche du mot*/
bool in_fra(francais fra, wstring mot) 
{ 
	if (!fra) 
		return false ;
	if (in_fra_aux(traductions(fra), mot))
		return true ;
	else 
		return in_fra(cdr(fra), mot) ; 
}

/*Regarde dans les traductions. Entoure notre mot d'espaces pour ne pas
  valider lors de substrings mais seulement quand le mot seul est trouvé
  dans un segment.*/
bool in_fra_aux(doublet dbt, wstring mot)
{ 	
	if (!dbt) 
		return false;
	
	wstring mot_seg = my_str_trim(mot, (my_len_str(mot) + 3)) ;
	wcsncpy((mot_seg + 1), mot, my_len_str(mot)) ;
	*mot_seg = ' ';
	*(mot_seg + (my_len_str(mot) + 1)) = ' ';
	  
	/*valide quand entrée est tel quel ou mot 
	  fait partie d'un segment de phrase*/
	if ((wcscmp(mot, mot(dbt)) eql 0) 
	   || (my_str_in_str(mot_seg, mot(dbt)) > 0) ) { 
	   	free(mot_seg) ;
		return true ; 
	}
	
	free(mot_seg) ;
	
	return in_fra_aux(cdr(dbt), mot) ; 
}


/*imprime les variables de la structure Japanese et appelle
des sous-fonctions pour imprimer les autres variables*/
void print_ent(entree ent)
{ 
	wchar_t buffer[128];
	if (!ent) //si résultats
		return ;
	widget_print(Current_Output, (wstring)L"\n\n");
	/*imprime le kanji que s'il existe*/
	if (kanji(original(ent))){
		swprintf(buffer, 128, L"kanji: %ls ", kanji(original(ent)));
		widget_print(Current_Output, buffer);
	}
	
	/*imprime le kana*/
	swprintf(buffer, 128, L"kana: %ls", kana(original(ent))) ;
	widget_print(Current_Output, buffer) ;
	
	bool trad_count = (compte_el(trad_et_cat(ent)) > 1);
	int idx = 1;
	
	/*le paramètre trad_count, avec l'index permet de mettre en page
	  différement selon qu'il y ait une seule traduction ou plusieurs.*/
	print_francais(trad_et_cat(ent), trad_count, idx);
	widget_print(Current_Output, (wstring)L"\n");
}

/*Appelle la fonction pour appeler les doublets et est récursif tant qu'il
y a des entrées*/
void print_francais(francais all_french, bool trad_count, int idx)
{ 
	wchar_t buffer[64];
	/*dépendemment du paramètre*/
	if (all_french) { 
		if (!trad_count) 
			widget_print(Current_Output, (wstring)L"\ntraduction:");
		else {
			swprintf(buffer, 64, L"\ntraduction n°%d:", idx);
			widget_print(Current_Output, buffer);
		}
		idx++ ;
		/*Imprime les catégories*/
		print_doublets(categories(all_french), (wstring) L".");
		/*Imprime les traductions*/
		print_doublets(traductions(all_french), (wstring) L","); 
		//récursif sur cdr
		return print_francais(cdr(all_french), trad_count, idx);
	}
	return ; 
}

/*Imprime chaque élément d'un doublet, prend un paramètre spécifiant
 un caractère à imprimer pour diviser les entrées.*/ 
void print_doublets(doublet all_doublets, wstring spec_car)
{
	wchar_t buffer[256];
	if (all_doublets) { 
		if (cdr(all_doublets)){
			swprintf(buffer, 256, L" %ls%ls", mot(all_doublets), spec_car);
			widget_print(Current_Output, buffer);
		}
		else {
			swprintf(buffer, 256, L" %ls.", mot(all_doublets));
			widget_print(Current_Output, buffer);
		}
		
		return print_doublets(cdr(all_doublets), spec_car); 
	}
	
	return ; 
}
