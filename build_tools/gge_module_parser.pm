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
my @key_words = qw(make import exoprt);
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
	#my $section = '(.+)(?:\s+(.+))?';
	my $sec = "((?:$kw)" . '\s+(?:\w+)?)';
	my $begin_sec = '\/\/\s*gge_begin\s+' . $sec . '\n*';
	my $end_sec = '\/\/\s*gge_end\s+' . $sec . '\n*';

	#print "Looking for $sec\n";
	my @matches = $content =~ m/
		$begin_sec
		($cpp_code)
		$end_sec/xgs;
	for (@matches)
	{
		s/^\s|\t+//;
		s/\s|\t+$//;
		s/\/\/.+//;
	}

	return read_subsection(matches => \@matches);
	#die Dumper {matches => \@matches, section => $section} if $section;
}

sub read_subsection
{
	my %args = @_;
	my @matches = @{$args{matches}};
	my $key //= $args{key};
	#warn Dumper {subsec => \@matches, key => $key};
	my $subsection;
	for my $match (@matches)
	{
		if($match =~ m/($kw)(.+)/)
		{
			$key = $1.'_'.$2;
			shift @matches;
			pop @matches;
			$subsection->{$key} = read_subsection(matches => \@matches, key => $key);
		}
		elsif($key)
		{
			return {gge_utils::parse_functions($match)};
		}
		elsif($match )
		{
			warn "no key set for ".Dumper $match;
		}
	}
	return $subsection;
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
