#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use ggeb;

sub create_class
{
	my ($file_name_base, 
		$class_name, 
		$header_deps, 
		$src_deps,
		$parent_class_name,
		%fns) = @_;
	for my $file (qw(header source))
	{
		my ($file_name, $type, $code);
		if($file eq 'header')
		{
			$file_name = $class_name . '.hpp';
			$code = expand_declarations($class_name, %fns);
			$code = _header_template($class_name, $code, $header_deps, $parent_class_name);
			write_to_file(
				$code,
				$file_name_base . '.hpp'
			);
		}
		elsif($file eq 'source')
		{
			$file_name = $class_name . '.cpp';
			$code = expand_definitions($class_name, %fns);
			$code = _source_template($class_name, $code, $src_deps);
			write_to_file(
				$code,
				$file_name_base . '.cpp'
			);
		}
		else
		{
			die "not a file type";
		}
	}
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
		my $p_n = $fns{$fn_name}{paramters_names};
		my $fn_def = $fns{$fn_name}{definition};
		if($fn_name =~ /.+__\d+/)
		{
			$fn_name =~ s/(.+)__\d+/$1/;
		}
		$out .= <<eof;
$rt $class_name\::$fn_name($fp)
{
	$fn_def
}

eof
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
	$class_decl .= ": $parent_class" if ($parent_class);

	my $header = <<cls;
#pragma once
$includes

$class_decl
{
	public:
$content
};

cls
	return $header;
}

sub _source_template
{
	my ($name, $content, $class_deps) = @_;
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
