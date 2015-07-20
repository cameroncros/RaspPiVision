#!/usr/bin/tclsh
proc benchmark hash {
	puts $hash
	catch {exec git checkout $hash}
	catch {exec ./build.sh}
	catch {
		puts [exec ./benchmark.sh]
	}
}

set temp [catch {exec git checkout master}]
set a [split [exec git log | grep ^commit] \n]
foreach commit $a {
	set hash [lindex [split $commit " "] 1]
	benchmark $hash;
}
set temp [catch {exec git checkout master}]
