/*****************************
 ** Thai module for Tcl/Tk
 ** tcl_thchar.c : implementation of thctype for Tcl/Tk
 ** by Poonlap Veerathanabutr <poonlap@linux.thai.net>
 ** $Id: tcl_thchar.c,v 1.1 2001-09-25 15:46:47 poonlap Exp $
 ****************************/			    
#include<tcl.h>
#include<thai/thailib.h>
#include<thai/thctype.h>



/*
 *---------------------------------------------------------------------
 *
 * tcl_thchar --
 *      Classification of a given Thai character.
 *
 * Results:
 *      Return 1 or 0.
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Get Unicode string(char)
 *      2) convert to tis-620 char(simply - 0xD60)
 *      3) call th_isxxx provided by libthai
 *      4) return boolen obj or integer obj
 *
 *----------------------------------------------------------------------
 */
int tcl_thctype( ClientData client_data, Tcl_Interp *interp,
		 int objc, Tcl_Obj *CONST objv[]) { 
  Tcl_Obj *resultPtr;
  Tcl_UniChar *u;
  extern Tcl_HashTable thctypeTable;
  Tcl_HashEntry *entryPtr;
  int i;
  int (*handler)(thchar_t);
  char *option;
  /* Get resultPtr from interpreter */
  resultPtr = Tcl_GetObjResult(interp);
  
  
  if( objc >= 2 ){
    option = Tcl_GetString( objv[1]);
    u = Tcl_GetUnicode( objv[2] );
    entryPtr = Tcl_FindHashEntry( &thctypeTable, option);
    if( entryPtr == NULL ) {
      Tcl_AppendStringsToObj( resultPtr, "bad option\"", 
			      option,
			      "\": must be iseng isthai iscons istailless isovershoot isundershoot isundersplit isvowel isfv islv isuv isbv istone isdiac isdigit ispunct chlevel iscombchar",
			      (char *)NULL);
      return TCL_ERROR;
    } else if ( objc == 2){
      Tcl_WrongNumArgs( interp, 2, objv,
			"?thaichar?");
      return TCL_ERROR;
    }
    
    handler = (int(*)(thchar_t))Tcl_GetHashValue( entryPtr);
    if( handler == th_chlevel ){
      Tcl_SetIntObj( resultPtr, handler((thchar_t)(u[0] -0x0D60)) );
    } else {
      /* shift to tis-620 
	 get only the first character */
      Tcl_SetBooleanObj( resultPtr, handler((thchar_t)(u[0] - 0x0D60)) );
    }
    return TCL_OK;
  } else {
    Tcl_WrongNumArgs( interp, 1, objv,
		      "?class? ?thaichar?");
    return TCL_ERROR;
  } 
  
  return TCL_OK;
  
}


