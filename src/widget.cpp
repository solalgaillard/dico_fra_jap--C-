#include "widget.h"
#include "traduit.h"


/* =============================================== GLOBALES ==============================================*/

// pour avoir le dico dans Done()
extern entree dico_glb ;

// pour contrôler le curseur
extern XmTextPosition Start_pos ;
extern Widget Current_Output ;

/* =============================================== FONCTIONS ==============================================*/

// initialisation des widgets
Widget initMotifWidgets(Widget top_wid, XtAppContext app) 
{ 
	Widget main_window = XtVaCreateManagedWidget("main_window", xmMainWindowWidgetClass, top_wid, NULL) ;

	Widget menu_bar = XmCreateMenuBar(main_window, (String) "main_list", NULL, 0) ;
	XtManageChild(menu_bar) ;

	// créer le bouton quit avec son callback
	Widget quit = XtVaCreateManagedWidget("Quit", xmCascadeButtonWidgetClass, menu_bar, NULL);
	XtAddCallback(quit, XmNactivateCallback, quit_call, NULL) ;


	// créer la zone de saisie et ses ressources 
	Arg args[10];
	int n = initSetArg(args) ;

	Widget saisie = XmCreateScrolledText(main_window, (String) "saisie", args, n) ;
	XtManageChild(saisie) ;
	
	
	
	//définit la police du text widget au moyen de wild-cards afin 
	//qu'il trouve celle qui corresponde toujours au charset
	n = 0;
	XmRenderTable renderTable;
	XmRendition rendition;

	XtSetArg(args[n], XmNfontName, "-*-*-medium-r-normal-*-16-*-*-*-*-*-*-*"); 
	n++;
	XtSetArg(args[n], XmNfontType, XmFONT_IS_FONTSET); //fournit toutes polices
	n++;
	XtSetArg (args[n], XmNloadModel, XmLOAD_DEFERRED); 
	n++;

	rendition = XmRenditionCreate(saisie, (XmStringTag) "", args, n);
	renderTable = XmRenderTableAddRenditions(NULL, &rendition, 1, XmMERGE_REPLACE);

	XtVaSetValues(saisie, XmNrenderTable, renderTable, NULL);

	XmRenditionFree(rendition);
	XmRenderTableFree(renderTable);
  
    
	// gérer le retour-charriot
	static XtActionsRec actions[] = {{(String) "Done", Done}} ;
	XtAppAddActions(app, actions, XtNumber(actions));

	static ConstantString traduction = "<Key>Return: Done()" ;
	XtTranslations mytranslations = XtParseTranslationTable(traduction) ;
	XtOverrideTranslations(saisie, mytranslations) ;

	// gérer le curseur
	XtAddCallback(saisie, XmNmodifyVerifyCallback, control_insert, NULL) ;

	return saisie ;



}


// initialiser le tableau des ressources pour le widget texte
int initSetArg(Arg args[])
{
	int n = 0 ;
	XtSetArg(args[n], XmNrows, 30) ;		// longeur initiale
	n++ ;
	XtSetArg(args[n], XmNcolumns, 40) ;		// largeur initiale
	n++ ;
	XtSetArg(args[n], XmNeditable, True) ; 		// le texte est modifiable
	n++ ;
	XtSetArg(args[n], XmNcursorPositionVisible, True) ;	// le curseur est visible
	n++ ;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT) ;	// le widget comprend plusieurs lignes
	return n + 1 ;
}


// action lors d'un <Enter> : lance le read_eval_print
// boucler tant que le read n'a pas épuisé la ligne
// line contient toute la ligne
void Done(Widget text, XEvent * event, String * params, Cardinal * n)
{ 
	static wstring line = (wstring) malloc(BUFSIZ) ; // suffisant
	if (not (* (line = XmTextGetStringWcs(text) + Start_pos))) 
		return ;
	Current_Output = text ; //sauvegarde le widget saisie dans globale
	
	entree dico = dico_glb ;
	traduit(line, dico) ;
}


void widget_print(Widget W, wstring S)
{
	XmTextInsertWcs(W, XmTextGetLastPosition(W), S) ;
}

void widget_newpos(Widget W)
{ 
	Start_pos = XmTextGetLastPosition(W) ;
}


void quit_call(Widget W, XtPointer Ev, XtPointer client)
{ 
	printf("Quitting program\n"); exit(0); 
}

// callback empêchant l'insertion et la destruction ailleurs que dans la zone de saisie
// déclenché lors de toute tentative de modifier le texte
void control_insert(Widget W, XtPointer app_data, XtPointer call_data)
{
	XmTextVerifyCallbackStruct * call = (XmTextVerifyCallbackStruct *) call_data ;
	if ((call->reason == XmCR_MOVING_INSERT_CURSOR and call->newInsert < Start_pos )
		or call->startPos < Start_pos )
	{
		call->doit = False ; return ;
	}
	return ;
}
