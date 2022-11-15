#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use ggeb;
use class_builder;
use Data::Dumper;
use parse_templates;
use gge_modules;

$ggeb::debug = 0;
my $gge_modules = new gge_modules();
my @headers = ggeb::get_headers();
my $command_hpp = ggeb::slurp_file('src/commands/command.hpp');
my $ctor = gge_utils::read_section('export ctor', $command_hpp);
my @commands; #enum

for (keys %$gge_modules)
{
	my $class_name = $gge_modules->{$_}->{class_name} . '_command';
	my $class_callee = $gge_modules->{$_}->{class_name}; # the one the commands call
	# create command constructor for childrens' constructor
	# IF there are commands to be made
	if(exists $gge_modules->{$_}->{make_commands})
	{
		my %fns = gge_utils::parse_functions($ctor);
		my @v = values %fns;
		$gge_modules->{$_}->{parent_command_ctor} = $v[0];

		for my $function_name (keys %{$gge_modules->{$_}->{make_commands}})
		{
			my $command = make_command_enum(
					$class_callee, 
					$function_name,
					$gge_modules->{$_}->{make_commands}->{$function_name}->{parameters_names}
				);
			$gge_modules->{$_}->{make_commands}->{$function_name}->{enum} = $command;
			$gge_modules->{$_}->{make_commands}->{$function_name}->{definition} = 
				define_command($class_callee, $function_name, $gge_modules->{$_}->{make_commands}->{$function_name});
			push(@commands, $command);
		}

		# create the execute functions inherited from Command
		my $defs = mk_defs($gge_modules->{$_}->{make_commands}, $_);
		my $def_fns = join("\n", @$defs);
		my $definition =  <<eod; 
switch(_cmd) 
{
	$def_fns
};
eod
		$gge_modules->{$_}->{make_commands}->{execute} = {
			return_value => 'void',
			formal_parameters => '',
			parameters_names => '',
			definition => $definition};

		class_builder::create_class(
			'commands/'.lc($class_name), 
			$class_name, 
			['../'.lc($class_callee), 'command'], 
			['../'.lc($class_callee), lc($class_callee) . '_command'],
			{ parent => 'Command', ctor => $gge_modules->{$_}->{parent_command_ctor} },
			%{ $gge_modules->{$_}->{make_commands} }
		);
	}
}

# runner switch generation
die Dumper $gge_modules->{TEXTER};
#parse_templates::process_template('runner_switch.tmpl', {modules => $gge_modules} );


sub make_command_enum
{
	my ($class, $fn_name, $param_names) = @_;
	my $out = uc($class) . '_' . uc(gge_utils::demangle_name($fn_name));
	$out .= '_' . uc($param_names) if $param_names;
	return $out;
}

sub define_command
{
	my ($class_name, $fn_name, $fns) = @_;
	my $arg = $fns->{parameters_names};
	my $out = "static_pointer_cast<$class_name>(_module)->$fn_name($arg);";
}

sub def_command
{
	my ($fn_name, $fn_names, $class_name) = @_;
	$fn_name = gge_utils::demangle_name($fn_name);
	my $arg = "$fn_names";
	my $out = "static_pointer_cast<$class_name>(_module)->$fn_name($arg);";
	my ($param_names) = split('_', $fn_names);
	my $command = $class_name;
	$command .= '_' . $fn_name;
	$command .= '_' . $param_names if($param_names and $command !~ /$param_names/i);
	#push(@commands, uc($command));
	return $out;
}

sub mk_defs
{
	my ($fns, $cmd) = @_;
	my $defs = [];
	for my $fn_name (keys %$fns)
	{
		# can only every be one type
		my $type = $fns->{$fn_name}->{formal_parameters};
		$type =~ s/(.+)\s.+/$1/;
		push(@$defs, <<defs);
	// $_
	case($cmd): 
	{
		$fn_name(static_pointer_cast<$type>(arg_));
		break;
	};
defs
	}
	return $defs;
}
