#!/bin/perl

use Env (DDS_ROOT);
use lib "$DDS_ROOT/bin";
use Env (ACE_ROOT);
use lib "$ACE_ROOT/bin";

$opt = "-DCPSConfigFile rtps.ini";
sub run_pub()
{
	print "run \n";
	print "./publisher $opt \n";
	exec "./publisher $opt"
}

$numArgs = $#ARGV +1;
#print "$numArgs\n";
if($numArgs < 1)
{
	print "default\n";
}
elsif($numArgs =1)
{
	print "$ARGV[0]\n";
	if($ARGV[0] ==200 )
	{
		print "200\n";
	}
	elsif($ARGV[0] ==0)
	{
		run_pub();		
	}
	else
	{
		print "input 0 or 200\n";
	}
}
else
{
	print "input 0 or 200\n";
}
