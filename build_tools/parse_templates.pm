use Template;

my $tt = new Template(
	{INCLUDE_PATH => 'build_tools/templates/'},
);

sub process_template
{
	my ($template_name, $variables) = @_;
	$tt->process($template_name, $variables) or die $tt->error(), "\n";
}

1;
