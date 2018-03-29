#ifndef _DICO_JAP_FRA_H_
#define _DICO_JAP_FRA_H_

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

#define cdr(x) (x)->cdr
#define mot(x) (x)->mot
#define kana(x) (x)->kana
#define kanji(x) (x)->kanji
#define categories(x) (x)->categories
#define traductions(x) (x)->traductions
#define original(x) (x)->original
#define trad_et_cat(x) (x)->trad_et_cat

#define maximum 1024 //max size utilisé par buffer pour lire une ligne

#define NULLCHAR '\0'
#define eql ==
#define neql !=

typedef char * String ;
typedef char const * ConstantString ;
typedef wchar_t * wstring ;

/*structure de données du dictionnaire*/
typedef struct Doublet { wstring mot ; struct Doublet * cdr ; } * doublet ;
typedef struct Japanese { wstring kana ; wstring kanji ; } * japonais ;
typedef struct French { doublet categories ; doublet traductions ; struct French * cdr ; } * francais ;
typedef struct Entry { japonais original ; francais trad_et_cat ; struct Entry * cdr ; } * entree ;

#endif
