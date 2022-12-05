#!/usr/bin/perl
package gge_module_parser;
use strict;
use warnings;
use Data::Dumper;
use lib 'build_tools/';
use ggeb;
use gge_utils;

# just a catch all c++ code
our $cpp_code = '[.\/\"#\n\t\w\d,\s&*<>(){}\[\]:=;]+';
my @key_words = qw(make import export read write);
my $kw = join('|', @key_words);

my %sections;

sub parse_file
{
	my ($file, $import) = @_;
	print "Reading $file\n";
	return (read_section($file), gge_utils::find_parents($file));
}


# TODO cannot read nested commands...yet
sub read_section
{
	my ($file_name) = shift;
	my $content = slurp_file($file_name);

	my $sec = "((?:$kw)" . '\s+(?:\w+)?)';
	my $begin_sec = '\/\/\s*gge_begin\s+' . $sec . '\n*';
	my $end_sec = '\/\/\s*gge_end\s+' . $sec . '\n*';

	#print "Looking for $sec\n";
	my $sections;
	my @matches = $content =~ m/
		$begin_sec
		($cpp_code)
		$end_sec/xgs;

	my $c_kw = '';
	while(my $match = shift @matches)
	{
		#$match =~ s/\s+//;
		$match =~ s/\/\/.+//; # remove //-comments

		if($match =~ m/($kw)(.+)/)
		{
			print "Processing '$match'...";
			my $key = $1.'_'.$2;
			$key =~ s/\s+//;
			my $sec = shift @matches; # shift actual section
			$sections->{$key} = {gge_utils::parse_functions($sec)};
			my $end_kw = shift @matches;
			print "done!\n";
		}
		else
		{
			warn  "Expected [$kw] [name(s)]", Dumper $match;
			die Dumper \@matches;
		}
	}

	#die Dumper $file_name, $sections;
	return $sections; 
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

1;
