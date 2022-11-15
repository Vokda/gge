#!/usr/bin/perl

use strict;
use warnings;
use lib 'build_tools/';
use gge_utils;
use gge_modules;
use Data::Dumper;

my $modules = new gge_modules();
my $dir = 'src/';

for my $module (keys %$modules)
{
	my $ctor = make_ctor($module, $modules->{$module}->{export_ctor});
	gge_utils::expand_section($dir . 'gge_module_initalizer.hpp', 

}

sub make_ctor
{
	my $name = shift;
	my $data = shift;

	my $ctor;
	my $fn_name = lc($name);
	my $class_name = ucfirst($fn_name);
	my $params = $data->{$class_name}->{formal_parameters} // '';
	my $args = $data->{$class_name}->{parameters_names} // '';
	my $decl = "shared_ptr<GGE_module> $fn_name($params);";
	my $def =<<def;
shared_ptr<GGE_module> GGE_module_initializer::$fn_name($params)
{
	return make_shared<$name>($args);
}
def

	$ctor->{$name}->{decl} = $def;
	$ctor->{$name}->{def} = $decl;
	return $ctor;
}
