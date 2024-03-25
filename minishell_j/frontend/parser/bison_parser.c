%{
#include <stdio.h>
%}
//set tokens
%token NUMBER
%token WHITESPACE //space or tab
%token STRING_LITERAL
%token OPERATOR
%token CONTROL_OPERATOR//|,  ||, &&, ETC
%token REDIRECTION_OPERATOR// <, >, >>, <<
/* %token SINGLE_QUOTE
%token DOUBLE_QUOTE (delimiters of string tokens?)*/



//grammar rules:
%%
typedef enum e_token
{
	WHITESPACE,
	STRING_LITERAL,
	OPERATOR
}	t_token;