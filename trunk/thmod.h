/*****************************
 ** Thai module for Tcl/Tk
 ** thmod.h : header for Thai module
 ** by Poonlap Veerathanabutr <poonlap@linux.thai.net>
 ** $Id: thmod.h,v 1.3 2001-10-01 14:41:06 poonlap Exp $
 ****************************/			    
#include<tcl.h>
#include<tk.h>
#include<thai/thailib.h>
#include<thai/thctype.h>
#define PACKAGE_NAME "tcl_thmod"
#define TCL_THMOD_VERSION "0.2"



Tcl_Encoding tis620_enc;
Tcl_HashTable thctypeTable;


/*
 * thai words related commads
 */
extern int tcl_thword( ClientData client_data, Tcl_Interp *interp, 
		      int objc, Tcl_Obj *CONST objv[] );
extern int tcl_thline( ClientData client_data, Tcl_Interp *interp, 
		      int objc, Tcl_Obj *CONST objv[] );
/*
 * thai character classification
 */
extern int tcl_thctype( ClientData client_data, Tcl_Interp *interp, 
			int objc, Tcl_Obj *CONST objv[] );
