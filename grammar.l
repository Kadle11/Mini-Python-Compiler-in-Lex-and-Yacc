%{
	#include <string.h>
	#include "y.tab.h"
	#define stack_size 100
	//#define DEBUG 1
	
	int yycolumn = 1;
	int startFlag = 1;
	
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; 		\
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; 	\
    yycolumn += yyleng;												
    
 	static int sp=0, stack [stack_size];
 	
 	static void debug(const char *X)
 	{
 		#ifdef DEBUG
 		if(startFlag)
 		{
 			printf("1 ");
 			startFlag=0;
 		}
 		if(strcmp(X, "NL")==0)
 		{
 			printf("%s\n%d ", X, yylineno);
 		}
		else
		{
			printf("%s ", X);	
		}
 		#endif
 	}
 	static void push (int i) 
 	{
   		if (++sp<stack_size) stack[sp]= i;
   		else {printf ("error: stack overflow\n"); exit(1);}
 	}
 	
 	int pop () 
 	{
   		if (sp>-1) return stack[sp--];
   		else {printf ("error: stack underflow\n"); exit(1);}
 	}
 	
 	int top()
 	{
 		if(sp>-1) return stack[sp];
 		else return 1;
 	}
 	
 	static int indent_depth(const char *K)
	{
		int len = strlen(K), i, tab_count=1;
		for(i=0; i< len ; i++)
		{
			if(K[i]=='\t')
			{
				tab_count++;
			}	
		}
		return tab_count;
	}	
 	int depth = 1;
 		
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
				yylval.depth = depth;
				debug("DD");
				return DD;
			}
			
			if(depth == top())
			{
				debug("ND");
				yylval.depth = depth;
				return ND;				
			}
			if(depth > top())
			{
				push(depth);
				debug("ID");
				yylval.depth = depth;
				return ID;
			}
			
		}

"import" {debug("IMPT"); return T_Import;}
"print"  {debug("Print"); return T_Print;}
"pass" {debug("Pass"); return T_Pass;}
"if" {debug("If"); return T_If;}
"while" {debug("While"); return T_While;}
"break" {debug("Break"); return T_Break;}
"and" {debug("And"); return T_And;}
"or" {debug("Or"); return T_Or;}
"not" {debug("Not"); return T_Not;}
"elif" {debug("Elif"); return T_Elif;}
"else" {debug("Else"); return T_Else;}
"def" {debug("Def"); return T_Def;}
"return" {debug("Return"); return T_Return;}
":" {debug("Cln"); return T_Cln;}
">" {debug("GT"); return T_GT;}
"<" {debug("LT"); return T_LT;}
">=" {debug("EGT"); return T_EGT;}
"<=" {debug("ELT"); return T_ELT;}
"==" {debug("EQ"); return T_EQ;}
"!=" {debug("NEQ"); return T_NEQ;}
"True" {debug("True"); return T_True;}
"False" {debug("False"); return T_False;}
"+" {debug("PL"); return T_PL;}
"-" {debug("MN"); return T_MN;}
"*" {debug("ML"); return T_ML;}
"/" {debug("DV"); return T_DV;}
"(" { debug("OP"); return T_OP;}
")" {debug("CP"); return T_CP;}
"[" {debug("OB"); return T_OB;}
"]" {debug("CB"); return T_CB;}
"," {debug("Comma"); return T_Comma;}
"=" {debug("EQL"); return T_EQL;}
"range" {debug("Range"); return T_Range;}
"list" {debug("List"); return T_List;}
[0-9]+ {yylval.text = strdup(yytext); debug("Number"); return T_Number;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); debug(yylval.text); return T_ID;}
\"([^\"\n])*\" {yylval.text = strdup(yytext); debug("String"); return T_String;}
\'([^\'\n])*\' {yylval.text = strdup(yytext); debug("String"); return T_String;}
"#"([a-z]|[0-9]|[A-Z]|" ")* {}
{whitespace} {} 
"\n" {yycolumn=1; debug("NL"); return T_NL;}
<<EOF>> {debug("EOF"); return T_EndOfFile;}

%%
