#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use gge_modules;
use parse_templates;
use Data::Dumper;
use gge_utils;

my @headers = gge_utils::get_headers();
my @ctors = ();
for my $h (@headers)
{
	my $text = gge_utils::slurp_file('src/'.$h);

	push(@ctors, 


print Dumper $gge_modules;
