#include "to_struct.h"
#include "str_list_ctrl.h"

/*Fonction de contrôle qui ouvre le fichier 
  du dictionnaire et appelle les fonctions 
  qui vont créer la structure.*/
entree file_to_struc()
{
	FILE * dico = fopen("./src/dico_japonais-francais", "r") ; 
	if (! dico) 
		usage((wstring)L"Le fichier du dictionnaire a été retiré ou est corrompu.") ;
	
	/*prendra les lignes du fichier dictionnaire*/
	wchar_t buffer[maximum] ;
	
	entree dico_entree  = NULL;
	
	/*Se débarasser de la 1ère ligne*/
	fgetws(buffer, maximum, dico);
	
	/*ensuite pour chaque ligne*/
	while (fgetws(buffer, maximum, dico))
		dico_entree = line_to_struc(buffer, dico_entree) ;

	
	fclose(dico) ;
	
	return dico_entree ;
	
}

/*si erreur on sort du programme*/
void usage(wstring message) 
{ 
	fprintf(stderr, "\n%ls\n", message) ; 
	exit(1) ; 
}

/*fonction qui découpe la ligne entre 
  partie japonaise et partie française au moyen du slash*/
entree line_to_struc(wstring ligne, entree old_ent)
{ 
	int slash = my_strchr_pos('/', ligne) ;
	entree ent = (entree)malloc(sizeof(struct Entry)) ;
	if (!ent)
		perror("malloc");
	  
	wstring buf_jap = my_str_trim(ligne, slash) ;  
	original(ent) = to_jap(buf_jap);
	free(buf_jap) ;
	
	trad_et_cat(ent) = to_fra((ligne + (slash + 1))) ;
	cdr(ent) = old_ent ;
	return ent ;
}
 
/*divise partie japonaise de la ligne (avant slash)
  entre kana et kanji. Le problème est que la ligne 
  est formatée différement selon qu'il existe une 
  écriture en kanji ou non*/	  
japonais to_jap(wstring ligne) 
{ 
	
	int cro_ouv = my_strchr_pos('[', ligne) ;
	int cro_fer = my_strchr_pos(']', ligne) ;
	
	japonais jap = (japonais)malloc(sizeof(Japanese)) ;
	if (!jap)
		perror("malloc");
	
	/*avec écriture en kanji donc kana entre crochets*/
	if (cro_fer >= 0) { 
		
		wstring buf_kanji = my_str_trim(ligne, cro_ouv) ;  
		
		int len_kana = cro_fer - cro_ouv ;
		wstring buf_kana = my_str_trim((ligne + cro_ouv +1), len_kana) ; 
	  	  
		kana(jap) = wcsdup(buf_kana) ;
		kanji(jap) = wcsdup(buf_kanji) ;
		free(buf_kana) ;
		free(buf_kanji) ;
		
	} else {
		
		/*sans écriture en kanji donc kana sans crochets*/
		wstring buf_kana = my_str_trim(ligne, my_len_str(ligne)+1) ;

		kana(jap) = wcsdup(buf_kana) ;
		kanji(jap) = NULL ;
		free(buf_kana) ;
	
	}
	
	return jap ; 
	
}

/*divise la partie française, un "//" indique la présence de plusieurs 
  traductions sémantiques possibles(pas des synonymes)*/
francais to_fra(wstring ligne)
{
	int dble_slash = my_str_in_str((wstring)L"//", ligne);
	
	francais fra = (francais)malloc(sizeof(struct French)) ;
	if (!fra)
		perror("malloc");
	
	if (dble_slash >= 0) { 
		
		wstring buf_cat_trad = my_str_trim(ligne, (dble_slash + 2)) ;  
		
		categories(fra) = to_cat(buf_cat_trad); 	  
		traductions(fra) = to_trad(buf_cat_trad, true, true);
		free(buf_cat_trad) ;
		cdr(fra) = to_fra(ligne + (dble_slash + 2));
		return fra ; 
	}
	
	categories(fra) = to_cat(ligne);
	traductions(fra) = to_trad(ligne, true, true);
	cdr(fra) = NULL;
	return fra ; 
}

/*divise la partie catégories de la partie française. Un mot peut
  avoir plusieurs catégories indiquées par des parenthèses.*/
doublet to_cat(wstring ligne)
{ 
	if(*ligne eql '(') { 
		doublet cat = (doublet)malloc(sizeof(struct Doublet)) ;
		if (!cat)
			perror("malloc");
		int par_ferm = my_strchr_pos(')', ligne) ;
		wstring buf_cat = my_str_trim((ligne + 1), par_ferm) ;

		mot(cat) = wcsdup(buf_cat) ;
		free(buf_cat) ;
		cdr(cat) = to_cat(ligne + (par_ferm + 1)) ;
		return cat;
	}
	return NULL ;
}

/*divise la partie traductions de la partie française. Un mot peut
  avoir plusieurs traductions (synonymes) divisés par des obliques.
  Il faut aussi prendre en compte qu'un mot peut suivre une catégorie
  donc une parenthèse et non pas une oblique.*/	
doublet to_trad(wstring ligne, bool ap_slash, bool ap_cat)
{ 
	int nxt_slash = my_strchr_pos('/', (ligne + 1)) ;
	if (nxt_slash < 0) return NULL ;
		
	bool aft_cat = (*ligne eql ' ') && ap_cat ;
	bool aft_slash = (*ligne neql '(') && ap_slash ;
	
	wstring buf_trad = my_str_trim(ligne, (nxt_slash + 2)) ;
	  
	if ((*ligne eql '/') || aft_cat) { 
		doublet trad = (doublet)malloc(sizeof(struct Doublet)) ;
		if (!trad)
			perror("malloc");
		mot(trad) = wcsdup((buf_trad+1)) ;
		free(buf_trad) ;
		cdr(trad) = to_trad((ligne + nxt_slash), false, false);
		return trad ; 
	}
	
	if (aft_slash) { 
		doublet trad = (doublet)malloc(sizeof(struct Doublet)) ;
		if (!trad)
			perror("malloc");
		mot(trad) = wcsdup(buf_trad) ;
		free(buf_trad) ;
		cdr(trad) = to_trad((ligne + nxt_slash), false, false);
		return trad ; 
	}
	free(buf_trad) ;
	return to_trad((ligne + 1), false, ap_cat); 
}

