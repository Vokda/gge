#!/usr/bin/perl
package gge_modules;
use strict;
use warnings;
use lib 'build_tools/';
use Data::Dumper;
use ggeb;
use gge_utils;
use gge_module_parser;
use gge_command_parser;

my $src_dir = 'src/';
my $reg_mod_file = $src_dir . 'registered_gge_modules.hpp';
my $commands_file = $src_dir . 'commands/command.hpp';
my @header_files;
#my $command_hpp = ggeb::slurp_file($commands_file);
#my $ctor = ggeb::read_section('export ctor', \$command_hpp);
my @commands;

# just a catch all c++ code
our $cpp_code = '[.\/\"#\n\t\w\d,\s&*<>(){}\[\]:=;]+';

sub new
{
	my $class = shift;
	my $self = get_modules();
	bless $self, $class;
	$self->get_header_files();
	for (keys %$self)
	{
		my $header = $src_dir . $self->{$_}->{header_file};
		# get commands among other things
		my ($sec, @parents) = gge_module_parser::parse_file($header);
		while ( my ($k, $v) = each %$sec)
		{
			$self->{$_}->{$k} = $v;
			# add command parent
		}
		if(@parents)
		{
			$self->{$_}->{parents} = \@parents;
		}
	};

	print "Found modules " . join(', ', keys %$self) . "\n";
	return $self;
}

sub get_modules
{
	my $modules = {};
	my $gge_modules = [get_gge_modules()];
	$modules = {map { $_ => {gge_module_name => $_} } @{$gge_modules}};
	$modules = get_class_names($modules);
	return $modules;
}

sub get_gge_modules
{
	my @modules;
	open(my $fh, '<', $reg_mod_file) or die $!;
	while(my $line = <$fh>)
	{
		if($line =~ /enum\s+registered_gge_module\s+{/)
		{
			$line =~ s/enum\s+registered_gge_module\s+{(.+)};/$1/;
			$line =~ s/[\s\n]+//g;
			@modules =  split(',', $line);
			last;
		}
	}
	@modules = grep {$_ ne 'NONE'} @modules;
	return @modules;
}

sub get_class_names
{
	my ($modules) = shift;
	for my $module (keys %{$modules})
	{
		$modules->{$module}->{class_name} = classify_name($module);
	}
	return $modules;
}



sub get_module_exported_commands
{

	#ggeb::read_section
}

sub classify_name
{
	my ($name) = shift;
	my $class_name = substr($name, 0, 1) . lc(substr($name, 1));
	# special case of hex_grid
	$class_name = 'Hex_grid' if $class_name eq 'Grid';
	return $class_name;
}

sub get_header_files
{
	my $self = shift;
	for my $k (keys %$self)
	{
		my $header_file = lc($self->{$k}->{class_name}). '.hpp';
		$header_file = 'hex/' . $header_file if $header_file =~ m/hex/i;
		$self->{$k}->{header_file} = $header_file;
	}
}

sub generate_commands
{
	my $self = shift;
	die Dumper $self;
	# read commands
	print "generating commands\n";
	my @commands;
	open(my $fh, '<', $commands_file) or die $!;
	while(my $line = <$fh>)
	{
		if($line =~ /enum\s+commands\s+{/)
		{
			$line =~ s/enum\s+commands\s+{([,.]+)};/$1/;
			$line =~ s/[\s\n]+//g;
			@commands = split(',',$line);
			die Dumper \@commands;
			last;
		}
		else
		{
			next;
		}
	}
	for my $command (@commands)
	{
		my ($module, $fn, $arg) = split('_', $command);
		# arg MAY be part of fn name
		if(exists $self->{$module})
		{
		}


		#warn Dumper \@matches;
	}
}

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

sub demangle_fn_name
{
	my $name = shift;
	$name =~ s/(.+)__\d+/$1/;
	return $name;
}

1;
