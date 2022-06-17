#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use class_builder;
use Data::Dumper;
use parse_templates;
use gge_modules;

my $gge_modules = new gge_modules();

my @headers = get_headers();
my @commands;
for my $header (@headers)
{
	my $text = slurp_file($header);
	my $sec = read_section('make commands', \$text);
	if($sec)
	{
		my %fns = parse_functions($sec);
		$header =~ s/.+\/(.+)\.hpp/$1/;
		my $class_callee = classify_name($header);
		for (keys %fns)
		{
			$fns{$_}{definition} = def_command($_, $fns{$_}{parameters_names}, classify_name(uc $header)) // '';
		}
		my $class_name = classify_name( $header) . '_command';
		create_class(
			'commands/'.lc($class_name), 
			$class_name, 
			['../'.$class_callee, 'command'], 
			['../'.$class_callee],
			'Command',
			%fns
		);
	}
}

my $cmds = join(', ', sort(@commands));
my $enum = <<enum;
		enum command = {$cmds};
enum
my $command_hpp = slurp_file('src/commands/command.hpp');
expand_section(\$command_hpp, 'import commands', $enum);
write_to_file($command_hpp, 'commands/command.hpp');

# runner switch generation
warn Dumper $gge_modules;
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
