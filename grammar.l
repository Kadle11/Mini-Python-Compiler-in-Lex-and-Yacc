%{
	#include <string.h>
	#include "y.tab.h"
	#define stack_size 100
	
	int yycolumn = 1;
	
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; 		\
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; 	\
    yycolumn += yyleng; 												
    
 	static int sp=0, stack [stack_size];
 	static void push (int i) 
 	{
   		if (++sp<stack_size) stack[sp]= i;
   		else {printf ("error: stack overflow\n"); exit(1);}
 	}
 	
 	static int pop () 
 	{
   		if (sp>-1) return stack[sp--];
   		else {printf ("error: stack underflow\n"); exit(1);}
 	}
 	
 	static int top()
 	{
 		if(sp>-1) return stack[sp];
 		else return 0;
 	}
 	
 	static int indent_depth(const char *K)
	{
		int len = strlen(K), i, tab_count=0;
		for(i=0; i< len ; i++)
		{
			if(K[i]=='\t')
			{
				tab_count++;
			}	
		}
		return tab_count;
	}	
 	int depth = 0;
 		
%}
%option yylineno
whitespace [ ]
Multiline_comment \'\'\'.+\'\'\'
%%

[\t]*		{
			depth = indent_depth(yytext);
			//printf("Depth : %d ",  depth);
			if(depth < top())
			{
				while (depth < top()) pop();
				//printf("\tDD \n");
				return DD;
			}
			
			if(depth == top())
			{
				//printf("\tND \n");
				return ND;				
			}
			if(depth > top())
			{
				push(depth);
				//printf("\tID \n");
				return ID;
			}
		}
"import" {/*printf("IMPT \n");*/ return T_Import;}
"print"  {return T_Print;}
"pass" {return T_Pass;}
"if" {return T_If;}
"while" {return T_While;}
"break" {return T_Break;}
"and" {return T_And;}
"or" {return T_Or;}
"not" {return T_Not;}
"elif" {return T_Elif;}
"else" {return T_Else;}
"def" {return T_Def;}
":" {return T_Cln;}
">" {return T_GT;}
"<" {return LT;}
">=" {return T_EGT;}
"<=" {return T_ELT;}
"==" {return T_EQ;}
"!=" {return T_NEQ;}
"True" {return T_True;}
"False" {return T_False;}
"+" {return T_PL;}
"-" {return T_MN;}
"*" {return T_ML;}
"/" {return T_DV;}
"(" {return T_OP;}
")" {return T_CP;}
"[" {return T_OB;}
"]" {return T_CB;}
"," {return T_Comma;}
"=" {return T_EQL;}
[0-9]+ {yylval.text = strdup(yytext); return T_Number;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); return T_ID;}
\"([^\"\n])*\" {yylval.text = strdup(yytext); return T_String;}
\'([^\'\n])*\' {yylval.text = strdup(yytext); return T_String;}
"#"([a-z]|[0-9]|[A-Z]|" ")* {}
{whitespace} {} 
"\n" {return T_NL;}

%%
