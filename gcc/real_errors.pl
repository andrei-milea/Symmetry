use Term::ANSIColor ;#qw(:constants);


sub red {
	print color 'red';
	print @_;
	print color 'reset';
};



sub darkred {
	print color 'dark red';
	print @_;
	print color 'reset';
};

my $blue = sub {
	print color 'blue';
	print @_;
	print color 'reset';
	"";
};



sub under {
	print UNDERLINE; 
	print @_;
	#print color 'reset';
	print RESET;
}

sub yellow {
	print color 'yellow';
	print @_;
	print color 'reset';
}


sub colour_brackets {
	my ($text,$func) = @_;

	my $not_bracket = qr{[^\[\]]};
	my $bracket		= qr{[\[\]]};
	my $re = qr{^($not_bracket*)\[(.*)\](.*)$};
	if($text =~ /$re/ ) {
		#print "matched";
		print $func->($1);

		red("\n[");
		yellow("$2");
		red("]\n");
		print $func->($3);
	} else {
		#print "not matched";
		print $func->($text);
	};
	print color 'reset';
}



while(my $line = <>) {
	#print;
	

	#\todo -> modify regex to accept paths
	if($line =~ /^([a-zA-Z0-9\_]*\.[a-zA-Z0-9\_]*\:)(\d+)(.*)$/ ) {
		print $1;
		darkred($2);

		if($3 =~ /^(.*)(error:|note:|instantiated\ from)(.*)$/){ 
			print $1;
			darkred($2);
			#print $2;
			colour_brackets($3,$blue);
		} else {
			colour_brackets($3,$blue);
		};
	} else {
		colour_brackets($line,$blue);
	};


	print "\n";
}

=begin
print color 'bold red';
print "This text is bold blue.\n";


print color 'reset';
print "This text is normal.\n";


=cut
