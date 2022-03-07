#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my $src_dir = 'src/';
my $header = $src_dir . 'moduler.hpp';
my $source = $src_dir . 'moduler.cpp';

use lib 'build_tools/';
use ggeb;

my %gge_modules;

my $moduler_content = slurp_file($header);
my @modules = get_gge_modules();
my @classes = map{classify_name($_)} @modules;

for my $m (0 .. scalar @modules -1)
{
	$gge_modules{$modules[$m]} = {class_name => $classes[$m]};
}

for my $key (keys %gge_modules)
{
	my $class_name = $gge_modules{$key}{class_name};
	my $path = $class_name eq 'Hex_grid' ? 'hex/' : '';
	my $basename = $path . lc $class_name;
	$gge_modules{$key}{basename} = $basename;
	$gge_modules{$key}{header} = $gge_modules{$key}{basename} . '.hpp';
	$gge_modules{$key}{source} = $gge_modules{$key}{basename} . '.cpp';
	$gge_modules{$key}{include} = '#include "' . $gge_modules{$key}{header} . '"';
	# get constructor args
	my $header_content = slurp_file($src_dir.$gge_modules{$key}{header}, $class_name);
	$gge_modules{$key}{ctor_args} = get_ctor($header_content, $gge_modules{$key}{class_name});
	$gge_modules{$key}{ctor_args_names} = get_ctor_names($gge_modules{$key}{ctor_args});
}

my $moduler_source = slurp_file($source);
my (@fn_decls, @fn_defs, @header_includes, @includes);

# TODO automate template definitions
for my $module (@modules)
{
	my $class_name = $gge_modules{$module}{class_name};
	print "Generating functions for $class_name...";
	my $ctor_args = $gge_modules{$module}{ctor_args};
	my $ctor_args_names = $gge_modules{$module}{ctor_args_names};
	push(@header_includes, $gge_modules{$module}{include});
	# setters
	push(@fn_defs, "\t\tvoid set_module($ctor_args);");
	push(@includes, $gge_modules{$module}{include});
	push(@fn_decls, <<def);
void Moduler::set_module($ctor_args)
{ 
	cout << \"Module $class_name initialization...\" << endl;
	_modules[$module] = make_shared<$class_name>($ctor_args_names); 
	cout << \"Module $class_name initialization complete!\" << endl;
}
def
	# getters
	push(@fn_defs, <<decl);
		template<>	
			shared_ptr<$class_name> get_module() { return static_pointer_cast<$class_name>(_modules[$module]); }
decl
	print "done!\n";
}

# special_case
push(@header_includes, '#include "hex/orientation.hpp"');

expand_section(\$moduler_content, 'includes', join("\n", @header_includes));
expand_section(\$moduler_content, 'functions', join("\n", @fn_defs));
expand_section(\$moduler_source, 'fn_defs', join("\n", @fn_decls));
expand_section(\$moduler_source, 'includes', join("\n", @includes));

#warn Dumper $moduler_content;
#warn "----------------------------------------------\n";
#warn Dumper $moduler_source;

write_to_file($moduler_content, $header);
write_to_file($moduler_source, $source);
