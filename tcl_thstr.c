/*
 * tcl_thstr.c --
 *    Thai string related commands implementation.
 *
 * Copyright (c) 2001 Poonlap Veerathanabutr <poonlap@linux.thai.net>
 * 
 * $Id: tcl_thstr.c,v 1.1 2001-10-02 13:30:14 poonlap Exp $
 * 
 */
#include "thmod.h"
#include<tcl.h>
#include<thai/thailib.h>
#include<thai/thstr.h>


/*
 *---------------------------------------------------------------------
 *
 * tcl_thcode --
 *      Get Thai string and return the list of characters' code
 *
 * Results:
 *      List of haxadecimal vaules
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Print the string values when encoding name is given
 *
 *----------------------------------------------------------------------
 */
int  
tcl_thcode( ClientData client_data, Tcl_Interp *interp,
	    int objc, Tcl_Obj *CONST objv[]) { 
  Tcl_UniChar *u;
  unsigned char *utf;
  thchar_t *tis;
  Tcl_DString ds;
  int utf_byte;
  char output[8];
  int i;
  Tcl_Obj *resultPtr;
  extern Tcl_Encoding tis620_enc;
  unsigned char *s;
  int sn;
  
  if( objc < 2 || objc > 3){
    Tcl_WrongNumArgs( interp, 1, objv,
		      "thai_string ?options?");
    return TCL_ERROR;
  } 
  resultPtr = Tcl_GetObjResult(interp);
  
  utf = Tcl_GetStringFromObj( objv[1], &utf_byte);

  if( objc==2 || (objc == 3 && strcmp(Tcl_GetString(objv[2]), "-tis") == 0)){
    tis = Tcl_UtfToExternalDString( tis620_enc, utf, utf_byte, &ds);
    for( i=0; i<Tcl_DStringLength(&ds); i++){
      sprintf( output, "0x%02X", tis[i]);
      Tcl_AppendStringsToObj( resultPtr,
			      output, " ",
			      (char *)NULL);
    }
  } else if( objc==3 && 
	     strcmp(Tcl_GetString(objv[2]), "-unicode") == 0){
    u = Tcl_GetUnicode(objv[1]);
    for(i=0; i<Tcl_UniCharLen(u); i++){
      sprintf( output, "0x%04X", u[i]);
      Tcl_AppendStringsToObj( resultPtr,
			      output, " ",
			      (char *)NULL);
    }
  } else if( objc==3 && 
	     strcmp(Tcl_GetString(objv[2]), "-utf8") == 0){
    for(i=0; i<utf_byte; i++){
      sprintf( output, "0x%02X", utf[i]);
      Tcl_AppendStringsToObj( resultPtr,
			      output, " ",
			      (char *)NULL);
    }
  } else {
    Tcl_ResetResult(interp);
    Tcl_AppendResult( interp,
		      "Bad option \"",
		      Tcl_GetString(objv[2]),
		      "\": should be -tis, -utf8 or -unicode",
		      (char *)NULL);
    return TCL_ERROR;
      
      }
  
  
  return TCL_OK;
  
}


/*
 *---------------------------------------------------------------------
 *
 * tcl_thnorm --
 *      implementation of th_normalize
 *
 * Results:
 *      Return the normalized Thai string
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Get UTF-8 and unicode strings
 *      2) convert UTF-8 to tis
 *      3) call th_normalize
 *      4) convert to UTF-8
 *      5) return the result 
 *
 *----------------------------------------------------------------------
 */
int  
tcl_thnorm( ClientData client_data, Tcl_Interp *interp,
	    int objc, Tcl_Obj *CONST objv[]) { 
  
  extern Tcl_Encoding tis620_enc;
  unsigned char *utf, *s;
  int utf_byte;
  Tcl_DString ds;
  Tcl_Obj *resultPtr;
  thchar_t *tis;
  thchar_t *norm;
  
  if( objc != 2){
    Tcl_WrongNumArgs( interp, 1, objv,
		      "thai_string");
    return TCL_ERROR;
  }

  resultPtr = Tcl_GetObjResult(interp);

  utf = Tcl_GetStringFromObj( objv[1], &utf_byte);
  tis = Tcl_UtfToExternalDString( tis620_enc, utf, utf_byte, &ds);
  norm = (thchar_t *) Tcl_Alloc( sizeof(thchar_t) * 
				 (Tcl_DStringLength(&ds) + 1));
  th_normalize( norm, tis, Tcl_DStringLength(&ds)+1);
  Tcl_DStringFree(&ds);
  s = Tcl_ExternalToUtfDString( tis620_enc, norm, strlen(norm), &ds);
  Tcl_SetStringObj( resultPtr, s, Tcl_DStringLength(&ds));
  
  Tcl_Free((char *)norm);
  Tcl_DStringFree(&ds);
  return TCL_OK;
  
  

}
