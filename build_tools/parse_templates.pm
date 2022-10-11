use Template;

package parse_templates;

my $tt = new Template(
	{INCLUDE_PATH => 'build_tools/templates/'},
);

my $debug = 1;

sub process_template
{
	my ($template_name, $variables, $out) = @_;
	if(defined $out and $debug == 0)
	{
		$tt->process($template_name, $variables, $out) or die $tt->error(), "\n";
	}
	else
	{
		$tt->process($template_name, $variables) or die $tt->error(), "\n";
	}
}

1;
