#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use Data::Dumper;

our $debug;

sub create_class
{
	my (
		$file_name_base, 
		$class_name, 
		$header_deps, 
		$src_deps,
		$parent_class_name,
		%fns) = @_;
	print "Generating class $class_name.\n";
	#print "Header includes " . join(',', @$header_deps) . "\n";
	#print "Source includes " . join(',', @$src_deps) . "\n";
	#print "Parent class $parent_class_name\n" if $parent_class_name;
	for my $file (qw(header source))
	{
		my ($file_name, $type, $code);
		if($file eq 'header')
		{
			$file_name = $class_name . '.hpp';
			$code = expand_declarations($class_name, %fns);
			$code = _header_template($class_name, $code, $header_deps, $parent_class_name);
			ggeb::write_to_file(
				$code,
				$file_name_base . '.hpp'
			);
		}
		elsif($file eq 'source')
		{
			$file_name = $class_name . '.cpp';
			$code = expand_definitions($class_name, %fns);
			$code = _source_template($class_name, $code, $src_deps);
			ggeb::write_to_file(
				$code,
				$file_name_base . '.cpp'
			);
		}
		else
		{
			die "not a file type";
		}
	}
	print "Finished generating class $class_name.\n";
}

sub expand_declarations
{
	my ($class_name, %fns) = @_;
	my $out = '';
	$class_name //= '';
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
		$out .= <<eof;
\t\t$rt $fn_name($fp);
eof
	}

	return $out;
}

sub expand_definitions
{
	my ($class_name, %fns) = @_;
	my $out = '';
	$class_name //= '';
	for my $fn_name (keys %fns)
	{
		my $rt = $fns{$fn_name}{return_value};
		my $const = $fns{$fn_name}{is_const};
		my $fp = $fns{$fn_name}{formal_parameters};
		my $p_n = $fns{$fn_name}{parameters_names};
		my $fn_def = $fns{$fn_name}{definition};
		my $parent = $fns{$fn_name}{parent};
		if($fn_name =~ /.+__\d+/)
		{
			$fn_name =~ s/(.+)__\d+/$1/;
		}
		if($fns{$fn_name}{is_ctor})
		{
		$out .= <<eof;
$rt $class_name\::$fn_name($fp): $parent($p_n)
{
	$fn_def
}

eof
		}
		else
		{
		$out .= <<eof;
$rt $class_name\::$fn_name($fp)
{
	$fn_def
}

eof
		}
	}
	return $out;

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

sub _header_template
{
	my ($name, $content, $class_deps, $parent_class) = @_;
	die unless $name;

	my $includes = [map { '#include "'.$_.'.hpp"' } @$class_deps] // [];
	$includes = join("\n", @$includes);
	my $class_decl = "class $name";
	$class_decl .= ": public $parent_class" if ($parent_class);
	
	my $header = <<cls;
#pragma once
$includes

$class_decl
{
	public:
$content
};

cls

	warn Dumper $header if $debug;

	return $header;
}

sub _source_template
{
	my ($name, $content, $class_deps) = @_;
	$name = lc($name);
	my $includes = [map { '#include "'.$_.'.hpp"' } @$class_deps] // '';
	$includes = join("\n", @$includes);

	my $source = <<cls;
#include "$name.hpp"
$includes

$content
cls

	return $source;

}

1;
