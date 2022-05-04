#!/usr/bin/perl

use strict;
use warnings;

use lib 'build_tools/';
use ggeb;

my @modules = get_gge_modules();
my $content = slurp_file('src/gge_module.hpp');
my $cases;
for (@modules)
{
	$cases .= add_case($_);
}
expand_section(\$content, 'cases', $cases);
write_to_file($content, 'gge_module.hpp');


sub add_case
{
	my $module = shift;
	my $class_name = classify_name($module);
	my $str = <<eof;
				case($module):
					return "$class_name";
eof
	return $str;
}
