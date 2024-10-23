%option noyywrap
 
%{
    void yyerror(char*);
    #include "calc.tab.h"
%}
 
%%
 
[0-9]+  {
            yylval = atoi(yytext);
            return INTEGER;
        }
 
    /* 运算符 */
[-+()=/*\n] {return *yytext;}

"++" {return INC_OP;}
"&*" {return AND_TIMES;}
"|*" {return OR_TIMES;}
 
    /* 空白被忽略 */
[ \t]    ;
 
    /* 其他字符都是非法的 */
.    yyerror("无效的输入字符");
 
%%