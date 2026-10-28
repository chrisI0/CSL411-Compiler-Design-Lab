
%{
#include "y.tab.h"
%}

%%
"for"                       { return FOR; }
"int"|"float"|"char"|"double" { return TYPE; }

[a-zA-Z_][a-zA-Z0-9]*       { return ID; }
[0-9]+                      { return NUM; }

"<="|">="|"=="|"!="|"<"|">" { return RELOP; }
"++"|"--"                   { return INC_DEC; }
"+="|"-="|"*="|"/="         { return ASSIGN_OP; }
"="                         { return '='; }

[ \t\n]+                    { /* Ignore whitespace */ }

.                           { return yytext[0]; }
%%

int yywrap(void)
{
    return 1;
}
