#!/usr/bin/perl

# gge builder

use strict;
use warnings;

my $src_dir = 'src/';
my $reg_mod_file = $src_dir . 'registered_gge_modules.hpp';
# just a catch all c++ code
my $cpp_code = '[.\/\"#\n\t\w\d,\s&*<>(){}\[\]:=;]+';

sub slurp_file
{
	my ($file) = @_;
	my $content;
	open(my $fh, '<', $file) or die "$file: ". $!;
	{
		local $/;
		$content = <$fh>;
	}
	return $content;
}

sub get_file_handle
{
	my ($file) = @_;
	open(my $fh, '<', $file) or die $!;
	return $fh;
}

sub classify_name
{
	my ($name) = @_;
	my $class_name = substr($name, 0, 1) . lc(substr($name, 1));
	# special case of hex_grid
	$class_name = 'Hex_grid' if $class_name eq 'Grid';
	return $class_name;
}

# only gets first ctor
sub get_ctor
{
	my ($content, $class) = @_;
	my ($ctor) = $content =~ m/$class \s* \(($cpp_code?)\);/x;
	$ctor =~ s/[\n\t]+//g;
	return $ctor || 'void';
}

sub get_ctor_names
{
	my ($ctor_args) = @_;
	my @ctor_args = split(',', $ctor_args);
	for my $c (@ctor_args)
	{
		$c =~ s/.+\s(\w+)$/$1/;
	}
	return join(', ', @ctor_args);
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
	return @modules;
}


sub expand_section
{
	my ($content, $section, $text) = @_;
	print "Expanding $section...";
	# /* gge_being $section */
	my $begin_sec = '\/\/\s*gge_begin\s+' . $section . '\n';
	my $end_sec = '\/\/\s*gge_end\s+' . $section . '\n';

	#warn "Incomplete section: $section!" if($$content =~ /$begin/ or );

	$$content =~ 
	s/
	($begin_sec)
	.+
	($end_sec)
	/$1\n$text\n$2/xgs;
	print "done!\n";
}

sub write_to_file
{
	my ($content, $file) = @_;
	open(my $fh, '>', $file);
	print $fh $content;
}

1;
