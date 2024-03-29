#!/usr/bin/perl

# gge builder
package gge_utils;
use strict;
use warnings;
use Data::Dumper;
use lib 'build_tools/';

my $src_dir = 'src/';
my $reg_mod_file = $src_dir . 'registered_gge_modules.hpp';
# just a catch all c++ code
our $cpp_code = '[.\/\"#\n\t\w\d,\s&*<>(){}\[\]:=;]+';
our $debug = 0;

sub get_headers
{
	my $dir = $1 // $src_dir;
	my $dh;
	opendir($dh, $dir) or die "$dir $!";
	my @headers = map { $dir . $_ } grep /\.hpp/, readdir($dh);
	closedir($dh);
	return @headers;
}

# for future sub
	#$line =~ s/^(\/\*).+$//g; # remove /**/ comments
	#$line =~ s/^.+(\*\/)$//g; # remove /**/ comments

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
	my $class_name = uc(substr($name, 0, 1)) . lc(substr($name, 1));
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
		$c =~ s/\n//;
		$c =~ s/^[\t\s]+//;
		$c =~ s/[\t\s]+$//;
		$c =~ s/.+\s(\w+)$/$1/;
	}
	return join(', ', @ctor_args);
}

sub parse_functions
{
	my ($text) = @_; 

	my @lines = split(';', $text);
	# clean up
	for my $line (@lines)
	{
		$line =~ s/(\s*\/\/(\s+\w+)+)+\n//;
		$line =~ s/^\s+//;
		$line =~ s/\s+$//;
	}
	@lines = grep { $_ ne '' } @lines;
	my %gge_fns;
	my $overload = 1;
	for my $line (@lines)
	{
		my ($return_value, $fn_name, $args) = $line =~ /
		(?:($cpp_code)+ # return value 
		\s+)?
		($cpp_code)+ # fn name
		\(($cpp_code)*\) # parameters
		/ix;
		die "not a function? ---\n$line\n---" unless $fn_name;

		# add __ and n to the nth overloaded function
		$fn_name .= '__' . $overload++ if(exists $gge_fns{$fn_name});

		$gge_fns{$fn_name} = 
		{
			return_value => $return_value,
			formal_parameters => $args // '',
		};

		my @pt = map { 
			my $s = $_; 
			$s =~ s/^[\s\n]+//; 
			$s =~ s/[\s\n]+$//; 
			$s =~ s/^($cpp_code)\s.+$/$1/; $s 
		} split(',', $args) if ($args);
		$gge_fns{$fn_name}{parameters_types} = \@pt;
		if(not $return_value)
		{
			warn "no return value, assuming constructor!";
			$gge_fns{$fn_name}{is_ctor} = 1;
			$gge_fns{$fn_name}{return_value} = '';
		}
		$gge_fns{$fn_name}{parameters_names} = get_ctor_names($gge_fns{$fn_name}{formal_parameters}) // '';
		$gge_fns{$fn_name}{is_const} = fn_is_const($line) ? 'const' : '';
	}
	return %gge_fns;
}


sub fn_is_const
{
	return $_[0] =~ /(const);?$/;
}

sub read_all_sections
{
	my ($section, $text) = @_;
	unless(defined $text)
	{
		my $caller = caller;
		die "No text to read! $caller";
	}

	unless($section)
	{
		my $caller = caller;
		die "No section to use on text! $caller";
	}

	my $begin_sec = qr/\/\/\s*gge_begin\s+($section)\n/;
	my $end_sec = '\/\/\s*gge_end\s+' . $section . '\n';

	print "reading $text\n" if $debug;
	my ($sec, $content) = $text =~ /$begin_sec(.+)$end_sec/gs;

	$sec =~ s/\s+/_/g if $sec;
	warn Dumper $text, $begin_sec, $sec, $content if $debug;

	# it is possible to not find anything
	warn "No section '$section' in text!" if not($content) and $debug; 
	my %ret;
	$ret{$sec} = $content if $sec;
	return \%ret if $content;
}

sub read_section
{
	my ($section, $text) = @_;
	unless(defined $text)
	{
		my $caller = caller;
		die "No text to read! $caller";
	}

	unless($section)
	{
		my $caller = caller;
		die "No section to use on text! $caller";
	}

	my $begin_sec = '\/\/\s*gge_begin\s+' . $section .'\n';
	my $end_sec = '\/\/\s*gge_end\s+' . $section . '\n';

	print "reading $text\n" if $debug;
	my ($content) = $text =~ /$begin_sec(.+)$end_sec/gs;

	warn Dumper $text, $begin_sec, $content if $debug;

	# it is possible to not find anything
	warn "No section '$section' in text!" if not($content) and $debug; 
	return $content if $content;
}

sub expand_section
{
	my ($content, $section, $text) = @_;
	print "Expanding \"$section\"...";
	# /* gge_being $section */
	$section =~ s/\s/\\s/g;
	my $begin_sec = '\/\/\s*gge_begin\s+' . $section . '\n';
	my $end_sec = '\/\/\s*gge_end\s+' . $section . '\n';

	warn "Incomplete section: $section!" if($$content !~ /$begin_sec/ or $$content !~ /$end_sec/);

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
	my ($content, $file, $debug) = @_;
	my $file_name = $src_dir . $file;
	if($debug)
	{
		warn Dumper $content; 
		return;
	}
	open(my $fh, '>', $file_name) or die $file_name . ": $!";
	print $fh $content;
	close $fh;
}

sub demangle_name
{
	my $name = shift;
	$name =~ s/(.+)__\d+/$1/;
	return $name;
}

# find parents of a class
sub find_parents
{
	my ($file_name) = shift;
	my $content = slurp_file($file_name);
	my @parents = $content =~ m/class \w+:\s*public\s+(\w+)(?:\s*,?\s*public\s+(\w+))*/;
	@parents = grep defined, @parents;
	warn Dumper \@parents if $debug;
	return @parents;
}

1;
