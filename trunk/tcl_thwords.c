/*
 * tcl_thwords.c --
 *    Thai words related commands implementation.
 *
 * Copyright (c) 2001 Poonlap Veerathanabutr <poonlap@linux.thai.net>
 * 
 * $Id: tcl_thwords.c,v 1.2 2001-10-01 14:39:02 poonlap Exp $
 * 
 */
#include "thmod.h"
#include<tcl.h>
#include<thai/thailib.h>
#include<thai/thbrk.h>



/*
 *---------------------------------------------------------------------
 *
 * tcl_thword --
 *      implementation of th_brk + add on.
 *
 * Results:
 *      Return list of breakpoints or
 *      Return the Unicode Obj, including token at breakpoint
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Get UTF-8 and unicode strings
 *      2) convert UTF-8 to tis
 *      3) use th_brk to find breakpoints
 *      4) create new unicode string and insert token at those breakpoints
 *      5) return the result unicode string
 *
 *----------------------------------------------------------------------
 */
int  
tcl_thword( ClientData client_data, Tcl_Interp *interp,
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
  char brkpoint[8];
  Tcl_DString ds;
  unsigned char *s; /* store UTF-8 */
  Tcl_UniChar *token, *u, *r, *p;
  Tcl_UniChar b[1];
  b[0] = 0x003a; /* choose character : to be default token */
  b[1] = 0x0000; /* ending with NULL */
  
  resultPtr = Tcl_GetObjResult(interp);
  
  
  /* arguments parsing, the part that I hate */
  /* Please make it cleverer.                */
  if( objc >= 2 && objc <= 4){
    s = Tcl_GetStringFromObj( objv[1], &bl);
    ths = Tcl_UtfToExternalDString( tis620_enc, s, bl, &ds);
    pos = (int *)Tcl_Alloc( Tcl_DStringLength(&ds) * sizeof(int));
    cn = th_brk( ths, pos, Tcl_DStringLength(&ds));
    if( objc == 2){
      Tcl_ResetResult( interp);
      for(i=0; i<cn; i++){
	sprintf( brkpoint, "%d", pos[i]);
	Tcl_AppendStringsToObj( resultPtr, brkpoint, " ", (char *)NULL);
      }
    } else if ( strcmp( Tcl_GetString(objv[2]), "-insert") == 0){
      if( objc == 4 ){
	token = Tcl_GetUnicode(objv[3]);
      } else { /* objc == 3 */
	token = b;
      }
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
    } else {
      Tcl_AppendStringsToObj( resultPtr, "bad option \"",
			      Tcl_GetString(objv[2]), 
			      "\": must be -insert",
			      (char *)NULL);
      return TCL_ERROR;
    }
    Tcl_Free((char *)pos);
    return TCL_OK;
  } else {
    Tcl_WrongNumArgs( interp, 1, objv,
		      "thai_string ?-insert? ?token?");
    return TCL_ERROR;
  }
}


/*
 *---------------------------------------------------------------------
 *
 * tcl_thline --
 *      cut a long string into lines
 *      Do something like thword
 *
 * Results:
 *      Return list of breakpoints or
 *      Return the Unicode Obj, including token at breakpoint
 *
 * Side effects:
 *      none
 *
 * Algorithm:
 *      1) Get UTF-8 and unicode strings
 *      2) convert UTF-8 to tis
 *      3) use th_brk to find breakpoints
 *      4) create new unicode string and insert token at those breakpoints
 *      5) return the result unicode string
 *
 *----------------------------------------------------------------------
 */
int  
tcl_thline( ClientData client_data, Tcl_Interp *interp,
	    int objc, Tcl_Obj *CONST objv[]) { 
  extern Tcl_Encoding tis620_enc; 
  int i, j, k, cn, bl, ts, ul, rn, *pos, lineLength, charCount, lineBreak_n, *lineBreak;
  /* 
     i, j, k :   indexes
     cn :  break-point count
     bl :  byte size(length) 
     ts :  token size(number)
     ul :  unichar length
     rn :  result(unichar) length, including token
     pos : pointer to int for store breakpoint
     lineLength : number of character for one line
     charCount : counting characters
     lineBreak_n : number of breaked line
     lineBreak : list of line break points
  */
  Tcl_Obj *resultPtr;
  thchar_t *ths;
  char brkpoint[8];
  Tcl_DString ds;
  unsigned char *s;  /* store UTF-8 */
  Tcl_UniChar *token, *u, *r, *p;
  Tcl_UniChar b[1];
  b[0] = 0x000a; /* choose character \n to be default token */
  b[1] = 0x0000; /* ending with NULL */


  resultPtr = Tcl_GetObjResult(interp);
  
  
  if( objc >= 3 && objc <= 5){
    s = Tcl_GetStringFromObj( objv[1], &bl);
    if( Tcl_GetIntFromObj( interp, objv[2], &lineLength) == TCL_OK){
      if( lineLength <= 0 ){
	Tcl_AppendStringsToObj( resultPtr,
				Tcl_GetString(objv[2]),
				": the value should be greater than 0",
				(char *)NULL);
	return TCL_ERROR;
      }
    } else {
      return TCL_ERROR;
    }
    ths = Tcl_UtfToExternalDString( tis620_enc, s, bl, &ds);
    pos = (int *)Tcl_Alloc( Tcl_DStringLength(&ds) * sizeof(int));
    cn = th_brk( ths, pos, Tcl_DStringLength(&ds));
    lineBreak = (int *)Tcl_Alloc( ((int)(Tcl_DStringLength(&ds)/(float)lineLength)) * sizeof(int));
    charCount = lineLength;
    j=0;
    for( i=0; i<cn; i++){
      if( pos[i] > charCount ){
	charCount += lineLength;
	lineBreak[j] = pos[i];
	j++;
      }
    }
    lineBreak_n = j;
    Tcl_Free((char *)pos);
    

    if( objc == 3){
      for(i=0; i<lineBreak_n; i++){
	sprintf( brkpoint, "%d", lineBreak[i]);
	Tcl_AppendStringsToObj( resultPtr,
				brkpoint,
				" ",
				(char *)NULL);
      }
      Tcl_Free((char *)lineBreak);
      return TCL_OK;
    } else if( strcmp( Tcl_GetString(objv[3]), "-insert") == 0){
      if( objc == 5 ){
	token = Tcl_GetUnicode( objv[4]);
      } else {
	token = b;
      }
      u = Tcl_GetUnicode( objv[1]);
      ul = Tcl_UniCharLen(u);
      ts = Tcl_UniCharLen(token);
      rn = (ul+(lineBreak_n*ts));
      r = (Tcl_UniChar *)Tcl_Alloc( rn * sizeof(Tcl_UniChar));
      p = r;
      j = 0;
      for(i=0; i<ul; i++){
	if( i == lineBreak[j]){
	  for(k=0; k<ts; k++){
	    *p++ = token[k];
	  }
	  if( j != lineBreak_n -1 ){
	    j++;
	  }
	}
	*p++ = u[i];
      }
      Tcl_SetUnicodeObj( resultPtr, r, rn);       
      Tcl_Free((char *)r);
    } else {
      Tcl_AppendStringsToObj( resultPtr, "bad option \"",
			      Tcl_GetString(objv[3]), 
			      "\": must be -insert",
			      (char *)NULL);
      return TCL_ERROR;
    }
    
    
    
    
    
    Tcl_Free((char *)lineBreak);
    return TCL_OK;
  } else {
    Tcl_WrongNumArgs( interp, 1, objv,
		      "thai_string line_length ?-insert? ?token?");
    return TCL_ERROR;
  }
}

