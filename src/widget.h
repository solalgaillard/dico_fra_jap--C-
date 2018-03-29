#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "dico_jap_fra.h"
// pour openmotif
#include <Xm/Xm.h>		// la base
#include <Xm/Text.h> 		// pour les widgets de type texte
#include <Xm/MainW.h>		// fenêtres principales
#include <Xm/CascadeB.h>	// cascade button
#include <Xm/RowColumn.h>	// menu bar


//typedef Widget * output_widget ;

Widget initMotifWidgets(Widget, XtAppContext) ;

int initSetArg(Arg[]);

void Done(Widget, XEvent *, String *, Cardinal *) ;

void widget_print(Widget, wstring) ;

void widget_newpos(Widget);

void quit_call(Widget, XtPointer, XtPointer) ;

void control_insert(Widget, XtPointer, XtPointer) ;

#endif
