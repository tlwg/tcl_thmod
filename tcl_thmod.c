/*****************************
 ** Thai module for Tcl/Tk
 ** tcl_thmod.c : main module 
 ** by Poonlap Veerathanabutr <poonlap@linux.thai.net>
 ** $Id: tcl_thmod.c,v 1.1 2001-09-24 15:19:42 poonlap Exp $
 ****************************/			    
#include "thmod.h"

typedef struct {
  char *name;   /* type name */
  int (*type)(thchar_t);     /* pointer to th_isxx functions */
} ThctypeInfo;

/* Module initialization */
int Tcl_thmod_Init(Tcl_Interp *interp) {
  extern Tcl_Encoding tis620_enc;
  extern Tcl_HashTable thctypeTable;
  int newEntry;
  Tcl_HashEntry *entryPtr;
  ThctypeInfo *map;
  /* Hash table of thchar argument and function */
  ThctypeInfo thctypes[] = {
    {"isthai", th_isthai},
    {"iseng", th_iseng},
    {"istis" ,  th_istis},
    {"iscons", th_isthcons},
    {"istailless", th_istaillesscons},   /* tailless cons */
    {"isovershoot", th_isovershootcons}, /* overshoot cons */
    {"isundershoot", th_isundershootcons}, /* undershoot cons */
    {"isundersplit", th_isundersplitcons}, /* undersplit cons */
    {"isvowel", th_isthvowel},      /* Thai vowel */
    {"isfv", th_isflvowel}, /*   Thai following vowel */
    {"islv", th_isldvowel},  /*   Thai leading vowel */
    {"isuv", th_isupvowel},   /*   Thai upper vowel */
    {"isbv", th_isblvowel},  /*   Thai below vowel */
    {"istone", th_isthtone},       /* Thai tone mark */
    {"isdiac", th_isthdiac},       /* Thai diacritic */
    {"isdigit", th_isthdigit},       /* digit */
    {"ispunct", th_isthpunct},     /* punctuation */
    {"chlevel", th_chlevel},
    {"iscombchar", th_iscombchar},
    {(char *)NULL, 0}
  };
  
  Tcl_InitHashTable( &thctypeTable, TCL_STRING_KEYS);
  for( map=thctypes; map->name != NULL; map++){
    entryPtr = Tcl_CreateHashEntry( &thctypeTable, 
				    map->name,
				    &newEntry);
    Tcl_SetHashValue( entryPtr, map->type);
  }
  
  

  /* configure the encoding to Thai */
  Tcl_Eval( interp, "fconfigure stdin -encoding tis-620");
  Tcl_Eval( interp, "fconfigure stdout -encoding tis-620");  
  tis620_enc  = Tcl_GetEncoding( interp, "tis-620");
  

  /* 
   * Can not observe the effect of 
   * Tcl_Eval( interp, "encoding system tis-620");
   */
  
  
  
  
  /*
   * Register the new Tcl commands
   */
  Tcl_CreateObjCommand(interp, "thbrk", tcl_thbrk,
		       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateObjCommand(interp, "thbrk_insert", tcl_thbrk_insert,
		       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateObjCommand(interp, "thchar", tcl_thctype,
		       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

  /*
   * Declaration of package
   */
  Tcl_PkgProvide( interp, PACKAGE_NAME, TCL_THMOD_VERSION);
  return TCL_OK;
}
  
