# preprocess.pl
#
# Copyright (c) 2008-2009
# Steven Watanabe
#
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

#add "~" to the end of the backup file name
$^I = "~";

#read the whole file at once
undef $/;
use re 'eval' ;

$backslashed_lines = qr/(?>(?>\\(?>\n|\r\n)|.)*)/;
$string = qr/(?>\"(?>\\\\|\\\"|[^\"])*\"|'(?>\\\\|\\'|[^'])*')/;
$comment = qr{(?>//$backslashed_lines|/\*(?>[^*]|\*(?!/))*\*/)};
$pp = qr/(?>#$backslashed_lines)/;
$ignored = qr/(?>$string|$comment|$pp)/;
$parens = qr/(?>\((?>(?>(?>$ignored|[^()])+)|(??{$parens}))*\))/;
$ws = qr/(?:$comment|$pp|\s|(?:\\(?:\n|\r\n)))/;

$class_header = qr/(?>(?>\b(?:class|struct))(?>$ws+\w+)(?>(?>[^(){;=]|$parens|$ignored)*)\{)/;

$control = qr/(?:\b(?:__attribute__|__if_exists|__if_not_exists|for|while|if|catch|switch)\b)/;
$modifiers = qr/(?:\b(?:try|const|volatile)\b)/;
$start = qr/(?:^|\G|(?<=[{};]))(?>$ws*)/;
$body = qr/(?:(?!$control)(?>$ignored|[^{};]))/;
$end = qr/(?:$parens|\])/;
$body_start = qr/(?>$ws*(?:$modifiers$ws*)*\{)/;

$function_header = qr/(?>(?:$start)(?:$body*?$end)(?:$body_start))/;

@braces = ();

sub process {
    my $header = $_[0];
    my $open_brace = $_[1];
    my $close_brace = $_[2];

    if($header) {
        push(@braces, " TEMPLATE_PROFILE_EXIT() }");
        return("$header TEMPLATE_PROFILE_ENTER()");
    } elsif($open_brace) {
        push(@braces, "}");
        return($open_brace);
    } elsif($close_brace) {
        return(pop(@braces));
    } else {
        die("This should only be called if the pattern matched: \$$_[0],$_[1],$_[2],$_[3],\$");
    }
}

while(<>) {
    s/(($ignored)|((?>$class_header|$function_header))|([{])|([}]))/$2?$2:process($3,$4,$5)/ge;
    print "#include <template_profiler.hpp>\n";
    print;
}
