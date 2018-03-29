// prototypes de mes fonctions
#include "dico_jap_fra.h"
#include "widget.h"
#include "to_struct.h"
#include "traduit.h"

/* =============================================== GLOBALES ==============================================*/

entree dico_glb ;
XmTextPosition Start_pos = 0 ;
Widget Current_Output ;

/* =============================================== MAIN ==============================================*/

int main(int argc, char * argv[])
{
	/*afin d'imprimer les caractères japonais*/
	setlocale(LC_ALL, "en_US.utf8");
	XtSetLanguageProc(NULL, (XtLanguageProc) NULL, NULL);
	
	dico_glb = file_to_struc() ;
	
	XtAppContext interface ;
	
	Widget top_widget = XtVaAppInitialize(&interface, "Dictionnaire", NULL, 0, &argc, argv, NULL, NULL) ;
	
	Widget saisie = initMotifWidgets(top_widget, interface) ;
	

	// initialiser la zone de saisie
 	XmTextSetStringWcs(saisie, (wstring) L"dictionnaire-japonais-français> ") ;
  	Start_pos = 32 ;
  	XmTextSetCursorPosition(saisie, Start_pos) ;

	// affiche les widgets
	XtRealizeWidget(top_widget) ;
	// boucle principale
	XtAppMainLoop(interface) ;

  	return 0 ;
	
}

