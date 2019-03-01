%{
	#include <string.h>
	#include "y.tab.h"
	#define stack_size 100
	
	extern char* yylval;
	
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
"import" {/*printf("IMPT \n");*/ return IMPT;}
"print"  {return PRINT;}
"pass" {return PASS;}
"if" {return IF;}
"while" {return WHILE;}
"break" {return BREAK;}
"and" {return AND;}
"or" {return OR;}
"not" {return NOT;}
"elif" {return ELIF;}
"else" {return ELSE;}
"def" {return DEF;}
":" {return CLN;}
">" {return GT;}
"<" {return LT;}
">=" {return EGT;}
"<=" {return ELT;}
"==" {return EQ;}
"!=" {return NEQ;}
"True" {return TR;}
"False" {return FL;}
"+" {return PL;}
"-" {return MN;}
"*" {return ML;}
"/" {return DV;}
"(" {return OP;}
")" {return CP;}
"[" {return OB;}
"]" {return CB;}
"," {return CM;}
"=" {/*printf("EQL\n"); */return EQL;}
[0-9]+ {/*printf("NUM\n"); */return NUM;}
[_a-zA-Z][_a-zA-Z0-9]* {/*printf("VAR\n"); */return VAR;}
\"([^\"\n])*\" {/*printf("STR_CNST\n"); */return STR;}
\'([^\'\n])*\' {/*printf("STR_CNST\n"); */return STR;}
"#"([a-z]|[0-9]|[A-Z]|" ")* {}
{whitespace} {/*printf("Space\n");*/;} 
"'''" {/*printf("Trip_Quote\n"); */return Trip_Quote;}
"\n" {return NL;}

%%
