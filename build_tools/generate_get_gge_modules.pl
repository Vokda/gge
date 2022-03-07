#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my $src_dir = 'src/';
my $gge_module_file = $src_dir . 'gge_module.hpp';
my $out_file = $src_dir . 'get_gge_modules.generated';

print "Generating GGE modules getters...";
my @modules;
open(my $fh, '<', $gge_module_file) or die $!;
while(my $line = <$fh>)
{
	if($line =~ /enum\s+gge_module\s+{/)
	{
		$line =~ s/enum\s+gge_module\s+{(.+)};/$1/;
		$line =~ s/[\s\n]+//g;
		@modules =  split(',', $line);
		last;
	}
}
open(my $out_fh, '>', $out_file) or die $!;
my @output;
for my $module (@modules)
{
	my $class_name = substr($module, 0, 1) . lc(substr($module, 1));
	# special case of hex_grid
	$class_name = 'Hex_grid' if $class_name eq 'Grid';
	my $include = $class_name ne 'Hex_grid' ? $class_name : 'hex/' . $class_name;
	$include = lc($include);
	my $line = <<DEF;
#include "$include.hpp"
template<>
	shared_ptr<$class_name> get_module() { return static_pointer_cast<$class_name>(_modules[$module]); }
DEF
	push(@output, $line);
}

#die Dumper \@output;
print $out_fh join("\n", @output);
print "done!\n";
