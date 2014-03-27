finds
=====

Travel through file system and inspect regular files, printing out lines containing 
strings with a certain pattern.

Usage:	$finds -p pathname [-f c|h|S] [-l] -s s
	
	[-p pathname]:	required argument, which is the pathname need to search.
	[-f c|h|S]:	optional argument, which specifies the extensions of 
			  files that need to search. "c" means files with c extension.
	[-l]:		optional argument, which, when specified, means search for 
			  symbolic links as well.
	[-s s]:		required argument, which is specified by the -s flag and 
			  is followed by the search string "s".
			  

Note:
    Right now finds can NOT detect loops in symbolic link, i.e. it may go into a loop forever until some errors arise.
    
    And I didn't finish my_printf yet. Sorry about that.
