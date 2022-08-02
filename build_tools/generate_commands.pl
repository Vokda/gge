#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use class_builder;
use Data::Dumper;
use parse_templates;
use gge_modules;

our $debug = 1;

my $gge_modules = new gge_modules();
my @headers = ggeb::get_headers();
my $command_hpp = ggeb::slurp_file('src/commands/command.hpp');
my $ctor = ggeb::read_section('export ctor', \$command_hpp);
my @commands;
for my $header (@headers)
{
	my $text = ggeb::slurp_file($header);
	my $sec = ggeb::read_section('make commands', \$text);
	if($sec)
	{
		my %fns = ggeb::parse_functions($sec);
		$header =~ s/.+\/(.+)\.hpp/$1/;
		my $class_callee = ggeb::classify_name($header);
		for (keys %fns)
		{
			$fns{$_}{definition} = def_command($_, $fns{$_}{parameters_names}, ggeb::classify_name(uc $header)) // '';
		}
		my $class_name = ggeb::classify_name( $header . '_command' );
		# create constructor for children
		%fns = (%fns, ggeb::parse_functions($ctor));
		$fns{$class_name} = delete $fns{Command};
		$fns{$class_name}{parent} = 'Command';
		create_class(
			'commands/'.lc($class_name), 
			$class_name, 
			['../'.lc($class_callee), 'command'], 
			['../'.lc($class_callee)],
			'Command',
			%fns
		);
	}
}

my $cmds = join(', ', sort(@commands));
my $enum = <<enum;
		enum command {$cmds};
enum
ggeb::expand_section(\$command_hpp, 'import commands', $enum);
ggeb::write_to_file($command_hpp, 'commands/command.hpp');

# runner switch generation
#warn Dumper $gge_modules;
process_template('runner_switch.tmpl', {modules => $gge_modules});

sub def_command
{
	my ($fn_name, $fn_names, $class_name) = @_;
	$fn_name = demangle_fn_name($fn_name);
	my $out = "static_pointer_cast<$class_name>(_module)->$fn_name($fn_names);";
	my ($param_names) = split('_', $fn_names);
	my $command = $class_name;
	$command .= '_' . $fn_name;
	$command .= '_' . $param_names if($param_names and $command !~ /$param_names/i);
	push(@commands, uc($command));
	return $out;
}
