#!/bin/sh
#\
exec tclsh "$0" "$@"
# tis2utf.tcl -
# by Poonlap Veerathanabutr <poonlap@linux.thai.net>
# This sample doesn't need tcl_thmod, just only tis-620.enc
# Converting is done by Tcl command.
# $Id: tis2utf.tcl,v 1.1 2001-09-24 15:20:54 poonlap Exp $


# Check whether tis-620 is properly defined 
if {[lsearch -exact [encoding names] "tis-620"] == -1} {
    puts stderr "tis-620 encoding is not defined"
    exit -1;
}


if { $argc == 0 } {
    set input stdin
    set output stdout
} elseif {$argc == 1} {
    set input [open [lindex $argv 0]]
    set output stdout
} elseif { $argc == 2} {
    set input [open [lindex $argv 0]]
    set output [open [lindex $argv 1] w]
} 

fconfigure $input -encoding tis-620
fconfigure $output -encoding utf-8
# Change utf-8 to unicode if you want ucs-2 encoding

puts -nonewline $output [read $input]

exit 0

    



