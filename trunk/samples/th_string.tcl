#!/usr/bin/tclsh
# thai_string.tcl
# by Poonlap Veerathanabutr <poonlap@linux.thai.net>
# $Id: th_string.tcl,v 1.1 2001-10-02 13:34:30 poonlap Exp $



package require tcl_thmod

puts "Example of thnorm and thcode"
set in [encoding convertfrom tis-620 "ที่่อยู่"]
puts "Wrong sequence:$in [thcode $in]"
set out [thnorm $in]
puts "Nomalized sequence: $out [thcode $out]"

puts "\nPrint tis-620 codes"
puts "[thcode $out]"
puts "Print utf8 codes"
puts "[thcode $out -utf8]"
puts "Print unicode codes"
puts "[thcode $out -unicode]"

