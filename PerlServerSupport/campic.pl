#!/usr/bin/perl

use CGI qw(:standard);
use MIME::Base64 ();

print "Content-type: text/html\n\n";
print "Hello, World.", "<br>";


# open(FENCODED,">:raw", "/tstlog.uu");
# binmode(FENCODED);
# flock(FENCODED,2);
# print FENCODED $cvtbuf; 
# close(FENCODED);

$piclen = length param("testmsg");
if( (0 < $piclen) && (200000 > $piclen) ) {
#	Win32 open
#	open(FDECODED,">:raw", "/testimg.jpg");
#	unix open
	open(FDECODED,">/testimg.jpg");
	binmode(FDECODED);
	flock(FDECODED,2);
	print "Length of Test Message: ", $piclen, "<br>";
	($cvtbuf = param("testmsg")) =~ s/\s/+/g;
	print FDECODED MIME::Base64::decode($cvtbuf); 
	close(FDECODED);
	print "File Saved", "<br>";
} else {
	print "Error in File Size", "<br>";
}
