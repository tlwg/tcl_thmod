#!/usr/bin/tclsh
# th_wordbut.tcl -
# Sample on how to use thbrk and thbrk_insert
# by Poonlap Veerathanabutr <poonlap@linux.thai.net>
# $Id: th_wordcut.tcl,v 1.1 2001-09-24 15:20:54 poonlap Exp $

# Did you install tcl_thmod and tell tclsh how to find it?
package require tcl_thmod

# the following function do the same thing as thbrk_insert
# but may be slower. :-(
proc thbrk_line {thstr {brk :}} {
    set brkp [thbrk $thstr]
    set i 0
    foreach r $brkp {
	puts -nonewline [string range $thstr $i [expr $r - 1]]
	set i $r
	puts -nonewline $brk
    }
    puts -nonewline [string range $thstr $r end]
}

    
set ths [encoding convertfrom tis-620 ภาษาไทยวันละคำ]

puts "Input string: $ths"
puts "thbrk command returns list of breakpoints"
puts "[thbrk $ths]"
puts ""
puts "thbrk_line is a function defined by this script. \nIt does the same thing as thbrk_insert command does.\nOutput with default token:"
puts "[thbrk_line $ths ]"
puts "Output with token \"<WBR>\""
puts "[thbrk_line $ths <WBR>]"
puts ""
puts "Now use thbrk_insert(C) instead of thbrk_line(Tcl)"
puts "Results are the same but implpementations are different"
puts "thbrk_insert is written in C, so should be faster. :-)"
puts "[thbrk_insert $ths ]"
puts "[thbrk_line $ths <WBR>]"  
