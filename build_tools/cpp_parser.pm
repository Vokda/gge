#!/usr/bin/perl

package cpp_parser;

use warnings;
use strict;

# just a catch all c++ code
my $cpp_code = '[.\/\"#\n\t\w\d,\s&*<>(){}\[\]:=;]+';
my $debug = 0;

sub read_dir
{
	my ($dir) = @_;
}

sub read_file
{
	my ($file_name) = @_;
	my $slurp = slurp_file($file_name);
}

sub get_file_handle
{
	my ($file) = @_;
	open(my $fh, '<', $file) or die $!;
	return $fh;
}

sub slurp_file
{
	my ($file) = @_;
	my $content;
	open(my $fh, '<', $file) or die "$file: ". $!;
	{
		local $/;
		$content = <$fh>;
	}
	return $content;
}
