#!/usr/bin/perl

package gge_command_parser;
use strict;
use warnings;
use lib 'build_tools/';
use gge_utils;

my $src_dir = 'src/';
my $reg_mod_file = $src_dir . 'registered_gge_modules.hpp';

sub parse_commands
{
	my $header = shift;
	my $text = gge_utils::slurp_file($header);
	$text = gge_utils::slurp_file($reg_mod_file);
	my $section = gge_utils::read_section(qr/\w+\s+commands/, $text);

	my %commands;
}

sub _get_commands
{
	my $cmd = shift;
	$cmd =~ s/enum command ({[A-Z,]+})//;
}
