/*
 * tcl_thbrk.c --
 *    implementation of thwbrk in Tcl
 *
 * Copyright (c) 2001 Poonlap Veerathanabutr <poonlap@linux.thai.net>
 * 
 * $Id: tcl_thbrk.c,v 1.1 2001-09-24 15:19:42 poonlap Exp $
 * 
 */
#include "thmod.h"
#include<tcl.h>
#include<thai/thailib.h>
#include<thai/thbrk.h>



/*
 *---------------------------------------------------------------------
 *
 * tcl_thbrk --
 *      implementation of th_brk
 *
 * Results:
 *      Return the Tcl_List of break point
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Get UTF-8 string
 *      2) convert to tis-620 string
 *      3) call th_brk
 *      4) set list(string) and return
 *
 *----------------------------------------------------------------------
 */
int  
tcl_thbrk( ClientData client_data, Tcl_Interp *interp,
	   int objc, Tcl_Obj *CONST objv[]) { 
  extern Tcl_Encoding tis620_enc; 
  /* tis620_enc is defined in thmod.h and initilized in tcl_thmod.c */
  int i, cn, bl;
  Tcl_Obj *resultPtr;
  thchar_t *ths;
  int *pos;
  Tcl_DString ds;
  unsigned char *s;
  char brkpoint[8];

  resultPtr = Tcl_GetObjResult(interp);
  if( objc != 2){
    Tcl_WrongNumArgs( interp, 1, objv,
		      "thai_string");
    return TCL_ERROR;
  }
  
  s = Tcl_GetStringFromObj( objv[1], &bl);
  ths = Tcl_UtfToExternalDString( tis620_enc, s, bl, &ds);
  pos = (int *)Tcl_Alloc( Tcl_DStringLength(&ds) * sizeof(int));
  cn = th_brk( ths, pos, Tcl_DStringLength(&ds));
  Tcl_ResetResult( interp);
  for(i=0; i<cn; i++){
    sprintf( brkpoint, "%d", pos[i]);
    Tcl_AppendElement( interp, brkpoint);
  }
  
  Tcl_Free((char *)pos);
  return TCL_OK;
}


/*
 *---------------------------------------------------------------------
 *
 * tcl_thbrk_insert --
 *      like th_brk_line in libthai but don't use th_brk_line here.
 *
 * Results:
 *      Return the Unicode Obj, including breakpoint(token)
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Get UTF-8 and unicode
 *      2) convert UTF-8 to tis
 *      3) use th_brk to find breakpoints
 *      4) create new unicode string and insert token at those breakpoints
 *      5) return the result unicode string
 *
 *----------------------------------------------------------------------
 */
int  
tcl_thbrk_insert( ClientData client_data, Tcl_Interp *interp,
		  int objc, Tcl_Obj *CONST objv[]) { 
  extern Tcl_Encoding tis620_enc; 
  int i, j, k, cn, bl, ts, ul, rn, *pos;
  /* 
     i, j, k   indexes
     cn :  break-point count
     bl :  byte size 
     ts :  token size(number)
     ul :  unichar length
     rn :  result(unichar) length, including token
     pos : pointer to int for store breakpoint
  */
  Tcl_Obj *resultPtr;
  thchar_t *ths;
  Tcl_DString ds;
  unsigned char *s; /* store UTF-8 */
  Tcl_UniChar *token, *u, *r, *p;
  Tcl_UniChar b[1];
  b[0] = 0x003a; /* choose character : to be default token */
  b[1] = 0x0000; /* ending with NULL */

  resultPtr = Tcl_GetObjResult(interp);
  if( objc == 3){
    token = Tcl_GetUnicode( objv[2]);
  } else if( objc != 2){
    Tcl_WrongNumArgs( interp, 1, objv,
		      "thai_string ?break_string?");
    return TCL_ERROR;
  } else if( objc == 2){
    token = b; /* : */
  }
  
  s = Tcl_GetStringFromObj( objv[1], &bl);
  ths = Tcl_UtfToExternalDString( tis620_enc, s, bl, &ds);
  pos = (int *)Tcl_Alloc( Tcl_DStringLength(&ds) * sizeof(int));
  cn = th_brk( ths, pos, Tcl_DStringLength(&ds));
  u = Tcl_GetUnicode( objv[1]);
  ul = Tcl_UniCharLen(u);
  ts = Tcl_UniCharLen(token);
  rn = (ul+(cn*ts));
  r = (Tcl_UniChar *)Tcl_Alloc( rn * sizeof(Tcl_UniChar));
  /* Should I optimize the following code?, Any idea? */
  p = r;
  j = 0;
  for(i=0; i<ul; i++){
    if( i == pos[j]){
      for(k=0; k<ts; k++){
	*p++ = token[k];
      }
      if( j != cn -1 ){
	j++;
      }
    }
    *p++ = u[i];
  }
  

  Tcl_SetUnicodeObj( resultPtr, r, rn); 
  Tcl_Free((char *)r);
  Tcl_Free((char *)pos);
  
  return TCL_OK;
}



