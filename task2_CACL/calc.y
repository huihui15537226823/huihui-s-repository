%{
    #include <stdio.h>
    void yyerror(char*);
    int yylex(void);
%}

%token    INTEGER INC_OP AND_TIMES OR_TIMES
%left    '+' '-'
%left    '*' '/'
%nonassoc UMINUS
%right INC_OP AND_TIMES OR_TIMES

%%
program:
    program statement '\n'
    |
    ;
statement:
    expr    {printf("%d\n", $1);}
expr:
    INTEGER
    |'(' expr ')'    {$$ = $2;}
    |'-' expr %prec UMINUS { $$ = -$2; }
    |expr '+' expr    {$$ = $1 + $3;}
    |expr '-' expr    {$$ = $1 - $3;}
    |expr '*' expr    {$$ = $1 * $3;}
    |expr '/' expr    {$$ = $1 / $3;}
    |expr INC_OP expr    {$$ = $1 + ($3 + 1);}
    |expr AND_TIMES expr    {$$ = ($1 & $3) * $3;}
    |expr OR_TIMES expr    {$$ = ($1 | $3) * $3;}
    ;

%%
void yyerror(char* s)
{
    fprintf(stderr, "%s\n", s);
}

int main(void)
{
    printf("A simple calculator with special operations support.\n");
    yyparse();
    return 0;
}