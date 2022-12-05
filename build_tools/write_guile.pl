#!/usr/bin/perl

use warnings;
use strict;
use lib 'build_tools/';
use gge_utils;
use Data::Dumper;

my $guile_cpp = gge_utils::slurp_file('src/script_handling/guile.cpp');

my @subs_defined = split("\n", gge_utils::read_section('read subs', $guile_cpp));
s/^\s+|\s+$// for @subs_defined;
@subs_defined = grep { $_ } @subs_defined;

my @subs_to_export;
for my $sub (@subs_defined)
{
	if($sub =~ /(\".+\")/)
	{
		push(@subs_to_export, $1);
	}
}

my $export = 'scm_c_export(__subs__, NULL);';
my $subs = join(",\n", @subs_to_export);
$export =~ s/__subs__/$subs/;
warn Dumper \@subs_defined, \@subs_to_export, $export;
