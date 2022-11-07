#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use gge_utils;
use gge_modules;
use Data::Dumper;

my $modules = new gge_modules();


@ctors;
for my $module (keys %$modules)
{
	my $ctor = make_ctor($module, $modules->{$modules});
	die Dumper $ctor;

}

sub make_ctor
{
	my $name = shift;
	my $data = shift;
	my $ctor = <<EOF;
		case $gge
			{
				char* c = va_arg(args, char*);
				string s(c);
				size_t w = va_arg(args, unsigned);
				size_t h = va_arg(args, unsigned);
				gge_module = make_shared<GGE_module>(s, w, h);
			}
EOF



	return $ctor;
}
