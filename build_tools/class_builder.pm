#!/usr/bin/perl

package class_builder;
use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use Data::Dumper;
use parse_templates;

our $debug = 1;
my $path_to_src = 'src/';

sub create_class
{
	my (
		$file_name_base, 
		$class_name, 
		$header_deps, 
		$src_deps,
		$parent,
		%fns) = @_;
	print "Generating class $class_name.\n";
	if($debug)
	{
		print "Header includes " . join(',', @$header_deps) . "\n";
		print "Source includes " . join(',', @$src_deps) . "\n";
		print "Parent class $parent->{parent} \n" if $parent;
	}
	my $parent_class_name = $parent->{parent};
	for my $file (qw(header source))
	{
		my ($file_name, $type, $code);
		if($file eq 'header')
		{
			$file_name = $path_to_src . $file_name_base . '.hpp';
			my %header_data = expand_declarations($class_name, $parent, %fns);
			$header_data{class_name} = $class_name;
			$header_data{includes} = [map {'#include "'.$_.'.hpp"'} @$header_deps];
			$header_data{parent} = $parent->{parent};
			parse_templates::process_template('header.tmpl', \%header_data, $file_name);
		}
		elsif($src_deps and $file eq 'source')
		{
			$file_name = $path_to_src . $file_name_base . '.cpp';
			my %source_data = expand_definitions($class_name, %fns);
			$source_data{includes} = $src_deps;
			parse_templates::process_template('source.tmpl', \%source_data, $file_name);
		}
	}
	print "Finished generating class $class_name.\n";
}

sub expand_declarations
{
	my ($class_name, $parent, %fns) = @_;
	my %out;

	for my $fn_name (keys %fns)
	{
		my $rt = $fns{$fn_name}{return_value};
		my $const = $fns{$fn_name}{is_const};
		my $fp = $fns{$fn_name}{formal_parameters};
		my $p_n = $fns{$fn_name}{paramters_names};
		if($fn_name =~ /.+__\d+/)
		{
			$fn_name =~ s/(.+)__\d+/$1/;
		}
		$out{functions}{$fn_name} = "$rt $fn_name($fp);\n";
	}
	
	# create constructor
	if($class_name) 
	{
		if($parent)
		{
			my $fp = $parent->{ctor}->{formal_parameters};
			my $p_n = $parent->{ctor}->{parameters_names};
			my $parent_name = $parent->{parent};
			$out{constructor} = "$class_name($fp): $parent_name($p_n){}\n";
		}
		else
		{
			$out{constructor} = "$class_name(){};";
		}
	}

	return %out;
}

sub expand_definitions
{
	my ($class_name, %fns) = @_;
	my %out;
	for my $fn_name (keys %fns)
	{
		my $rt = $fns{$fn_name}{return_value};
		my $const = $fns{$fn_name}{is_const};
		my $fp = $fns{$fn_name}{formal_parameters};
		my $p_n = $fns{$fn_name}{parameters_names};
		my $fn_def = $fns{$fn_name}{definition} // '// NO DEFINITION';
		my $parent = $fns{$fn_name}{parent};
		if($fn_name =~ /.+__\d+/)
		{
			$fn_name =~ s/(.+)__\d+/$1/;
		}
		push(@{$out{functions}}, <<def);
$rt ${class_name}::$fn_name($fp)
{
	$fn_def
}
def
	}
	return %out;

}

sub demangle_fn_name
{
	my $fn_name = shift;
	if($fn_name =~ /.+__\d+/)
	{
		$fn_name =~ s/(.+)__\d+/$1/;
	}
	return $fn_name;
}

1;
