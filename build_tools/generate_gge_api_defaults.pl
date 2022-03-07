#!/usr/bin/perl

use strict;
use warnings;
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

# regex to capture type and variable name in c++
my $cpp_var = '[\w,\s&<>:]+';

my $text = read_file($gge_api_file);
$text =~ s/.+BEGIN EXPORT \*\/(.+)\/\* END EXPORT.+/$1/s;
my %exported_functions;
print "Generating GGE API defaults...\n";
for my $line (split(/;/, $text))
{
	next if($line =~ /\/{2,}/);
	if($line =~ /\w+\s*\w+\(/)
	{
		$line =~ s/^(\/\*).+$//g; # remove /**/ comments
		$line =~ s/^.+(\*\/)$//g; # remove /**/ comments
		my ($return_type, $fn_name) = $line =~ /($cpp_var)+\s(\w+)\(/;
		print "Processing $fn_name...";
		my ($formal_params) = $line =~ /\(($cpp_var)\)/gm;
		my ($is_const) = $line =~ /(const)$/;
		my @parameters = $formal_params ? split(/,/, $formal_params) : ('void');
		$return_type =~ s/\n\s*//g;
		s/^\s*(.+)\s*$/$1/ for @parameters;
		$exported_functions{$fn_name} = {
			function_name => $fn_name,
			return_type => $return_type,
			parameters => \@parameters,
			const => $is_const // ''
		};
		print "done!\n";
	}
	else
	{
		next;
	}
}

open(my $out_fh, '>', $out_file) or die $!;
my @output;
for my $fn_name (keys %exported_functions)
{
	my $rv = $exported_functions{$fn_name}->{return_type};
	my $params = join(',', @{$exported_functions{$fn_name}->{parameters}});
	my $const = $exported_functions{$fn_name}->{const};
	my $line = "{chaiscript::fun<$rv (GGE_API::*)($params) $const>(&GGE_API::$fn_name), \"$fn_name\"}";
	push(@output, $line);
}
#warn Dumper \%exported_functions;
print $out_fh join(",\n", @output);
print "Generation complete!\n";
