#!/bin/perl

use Env (DDS_ROOT);
use lib "$DDS_ROOT/bin";
use Env (ACE_ROOT);
use lib "$ACE_ROOT/bin";

$opt = "-DCPSConfigFile rtps.ini";
sub run_pub()
{
	print "run \n";
	print "./subscriber $opt \n";
	my $t = system("./subscriber $opt");
	print "end\n";
	print "t \n $t";
}

$numArgs = $#ARGV +1;
#print "$numArgs\n";
run_pub();		
