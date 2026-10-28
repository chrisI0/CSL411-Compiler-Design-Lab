
%{
#include "y.tab.h"
%}

%%
a       { return A; }
b       { return B; }
\n      { return '\n'; }
[ \t]   { /* Ignore spaces and tabs */ }
.       { return yytext[0]; }
%%

int yywrap(void)
{
    return 1;
}
