#!/usr/bin/perl

package class_builder;
use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use Data::Dumper;
use parse_templates;

our $debug = 0;
my $path_to_src = 'src/';

# expects
# class_spec = {
# functions => {fns},
# members => {}
#

sub create_class
{
	my %args = @_;
	#die Dumper \%args;
	my $file_name_base = $args{file_name_base};
	my $class_name = $args{class_name}; 
	my $header_deps = $args{header_deps}; 
	my $src_deps = $args{src_desp}; # no need to include header
	my $parent = $args{parent};
	my $class_spec = $args{class_spec};
	print "Generating class $class_name.\n";
	print Dumper $class_spec if $debug;
	if($debug)
	{
		print "Header includes " . join(',', @$header_deps) . "\n";
		print "Source includes " . join(',', @$src_deps) . "\n";
		print "Parent class $parent->{parent} \n" if $parent;
	}
	my $parent_class_name = $parent->{parent};
	my $file_name; 
	for my $file (qw(header source))
	{
		$file_name = $path_to_src . $file_name_base; # base
		my ($type, $code);
		if($file eq 'header')
		{
			my %header_data = expand_declarations($class_name, $parent, $class_spec);
			$header_data{class_name} = $class_name;
			$header_data{includes} = [map {'#include "'.$_.'.hpp"'} @$header_deps];
			$header_data{parent} = $parent->{parent};
			my $file = $file_name_base =~ s/^(.+\/)+//g;
			push(@$src_deps, $file); # add header to src includes
			parse_templates::process_template('header.tmpl', \%header_data, $file_name);
		}
		elsif($src_deps and $file eq 'source')
		{
			$file_name .= '.cpp';
			my %source_data = expand_definitions($class_name, $class_spec->{fns});
			$source_data{includes} = $src_deps;
			parse_templates::process_template('source.tmpl', \%source_data, $file_name);
		}
	}
	print "Finished generating class $class_name at $file_name.\n";
}

sub expand_declarations
{
	my ($class_name, $parent, $class_spec) = @_;
	my %out;

	my $fns = $class_spec->{fns};
	for my $fn_name (keys %{$class_spec->{fns}})
	{
		my $rt = $fns->{$fn_name}->{return_value};
		my $const = $fns->{$fn_name}->{is_const};
		my $fp = $fns->{$fn_name}->{formal_parameters};
		my $p_n = $fns->{$fn_name}->{paramters_names};
		if($fn_name =~ /.+__\d+/)
		{
			$fn_name =~ s/(.+)__\d+/$1/;
		}
		if($fns->{$fn_name}->{is_ctor})
		{
			$out{constructor} = "$class_name($fp);\n";
		}
		else
		{
			$out{functions}{$fn_name} = "$rt $fn_name($fp);\n";
		}
	}
	
	# create constructor borked
	#if($parent)
	#{
	#	my $fp = $parent->{ctor}->{formal_parameters};
	#	my $p_n = $parent->{ctor}->{parameters_names};
	#	my $parent_name = $parent->{parent};
	#	$out{constructor} = "$class_name($fp): $parent_name($p_n){}\n";
	#}
	#else
	#{
	#	$out{constructor} = "$class_name(){};";
	#}

	# add members
	$out{members} = [];
	my @members;
	for (keys %{$class_spec->{members}})
	{
		my $type = $class_spec->{members}->{$_}->{type};
		my $name = $class_spec->{members}->{$_}->{name};
		push(@members, $type . ' ' . $name . "\n");
	}
	$out{members} = \@members;
	return %out;
}

sub expand_definitions
{
	my ($class_name, $fns) = @_;
	my %out;
	for my $fn_name (keys %$fns)
	{
		my $rt = $fns->{$fn_name}->{return_value};
		my $const = $fns->{$fn_name}->{is_const};
		my $fp = $fns->{$fn_name}->{formal_parameters};
		my $p_n = $fns->{$fn_name}->{parameters_names};
		my $fn_def = $fns->{$fn_name}->{definition} // '// NO DEFINITION';
		my $parent = $fns->{$fn_name}->{parent};
		if($fn_name =~ /.+__\d+/)
		{
			$fn_name =~ s/(.+)__\d+/$1/;
		}
		my $fn;
		if($fns->{$fn_name}->{is_ctor})
		{
			$fn = <<def;
${class_name}::$class_name($fp)
{
	$fn_def
}
def
		}
		else
		{
			$fn = <<def;
$rt ${class_name}::$fn_name($fp)
{
	$fn_def
}
def
		}
		push(@{$out{functions}}, $fn);
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
