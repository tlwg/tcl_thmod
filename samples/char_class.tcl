#!/usr/bin/tclsh
# char_class.tcl -
# Demo of command thchar
# by Poonlap Veerathanabutr <poonlap@linux.thai.net>
# $Id: char_class.tcl,v 1.1 2001-09-24 15:20:54 poonlap Exp $

package require tcl_thmod

set in [open characters.txt]
fconfigure $in -encoding tis-620

while {[gets $in line] != -1} {
    
    set char [string index $line 1]
    puts "\t$char\t[thchar istis $char] \
	    [thchar iseng $char] \
	    [thchar isthai $char] \
	    [thchar iscons $char] \
	    [thchar istailless $char] \
	    [thchar isovershoot $char] \
	    [thchar isundershoot $char] \
	    [thchar isundersplit $char] \
	    [thchar isvowel $char] \
	    [thchar isfv $char] \
	    [thchar islv $char] \
	    [thchar isuv $char] \
	    [thchar isbv $char] \
	    [thchar istone $char] \
	    [thchar isdiac $char] \
	    [thchar isdigit $char] \
	    [thchar ispunct $char] \
	    [thchar chlevel $char] \
	    [thchar iscombchar $char]"
}
close $in
