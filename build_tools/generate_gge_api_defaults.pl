#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use Data::Dumper;

my $src_dir = 'src/';
my $scripter_file = $src_dir . 'scripter.cpp';
my $gge_api_file = $src_dir . 'gge_api.hpp';
my $out_file = $src_dir . 'gge_api_defaults.generated';

sub read_file
{
	my ($file) = @_;
	my $content;
	open(my $fh, '<', $file) or die $!;
	{
		local $/;
		$content = <$fh>;
	}
	return $content;
}

our $cpp_code;

my $text = read_file($gge_api_file);
$text =~ s/.+gge_begin export \*\/(.+)\/\* gge_end export.+/$1/s;
my %exported_functions;
print "Generating GGE API defaults...\n";
my %gge_fns = parse_functions($text);
open(my $out_fh, '>', $out_file) or die $!;
my @output;
for my $fn_name (keys %gge_fns)
{
	print "Processing $fn_name...";
	my $rv = $gge_fns{$fn_name}{return_value};
	my $params = $gge_fns{$fn_name}{formal_parameters};
	my $const = $gge_fns{$fn_name}{is_const};
	my $line = "{chaiscript::fun<$rv (GGE_API::*)($params) $const>(&GGE_API::$fn_name), \"$fn_name\"}";
	push(@output, $line);
	print "done!\n";
}
my $out = join(",\n", @output);
print $out_fh $out;
print "Generation complete!\n";
