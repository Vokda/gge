use Template;

package parse_templates;

my $tt = new Template(
	{INCLUDE_PATH => 'build_tools/templates/'},
);

my $debug = 0;

sub process_template
{
	my ($template_name, $variables, $out) = @_;
	warn "DEBUG mode: NOT writing to file\n" if $debug;
	die "no file suffix $out" if $out !~ /.+\..+$/;
	if(defined $out and $debug == 0)
	{
		if(-e $out)
		{
			warn "$out already exists! Not overwriting it!";
		}
		else
		{
			$tt->process($template_name, $variables, $out) or die $tt->error(), "\n";
		}
	}
	else
	{
		$tt->process($template_name, $variables) or die $tt->error(), "\n";
	}
}

1;
