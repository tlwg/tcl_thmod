#!/usr/bin/tclsh
# th_wordbut.tcl -
# Sample on how to use thword
# by Poonlap Veerathanabutr <poonlap@linux.thai.net>
# $Id: th_wordcut.tcl,v 1.2 2001-09-25 15:55:43 poonlap Exp $

# Did you install tcl_thmod and tell tclsh how to find it?
package require tcl_thmod

# the following function do the same thing as thword xxx -insert yyy
# but may be slower. :-(
proc thbrk_line {thstr {brk :}} {
    set brkp [thword $thstr]
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
puts "thword command returns list of breakpoints"
puts "[thword $ths]"
puts ""
puts "thbrk_line is a function defined by this script. \nIt does the same thing as thword with insert option do.\nOutput with default token:"
puts "[thbrk_line $ths]"
puts "Output with token \"<WBR>\""
puts "[thbrk_line $ths <WBR>]"
puts ""
puts "Now use thword xxx -insert yyy (C) instead of thbrk_line(Tcl)"
puts "Results are the same but implpementations are different"
puts "thword is written in C, so should be faster. :-)"
puts "[thword $ths -insert]"
puts "[thword $ths -insert <WBR>]"  
