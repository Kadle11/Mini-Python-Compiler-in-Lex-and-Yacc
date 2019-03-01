%{
	#include <stdio.h>
	#include <stdlib.h>
	
	extern int yylineno;
	
	typedef struct record
	{
		char type[10];
		char name[20];
	}
%}

%token NUM TR FL VAR SPC PRINT CLN NL EQL L_Paren R_Paren NEQ EQ GT LT EGT ELT OR AND NOT ID ND DD STR Trip_Quote HASH IF ELIF WHILE ELSE IMPT BREAK PASS MN PL DV ML OP CP OB CB DEF CM

%right EQL                                          
%left PL MN
%left ML DV

%%
StartDebugger : StartParse NL {printf("Valid Python Syntax\n"); exit(0);} ;
constant : NUM | STR ;
term : VAR | constant ;
StartParse : finalStatements ;
Expressions :  arith_exp | bool_exp ;
basic_stmt : pass_stmt | break_stmt | import_stmt | assign_stmt | Expressions | print_stmt;
arith_exp :  term | arith_exp  PL  arith_exp |
			    arith_exp  MN  arith_exp |
			    arith_exp  ML  arith_exp |
			    arith_exp  DV  arith_exp | 
			    OP arith_exp CP;
ROP : GT | LT | ELT | EGT  ;
bool_exp : TR | FL | OP bool_exp CP | arith_exp ROP arith_exp 
			 | bool_exp AND bool_exp
			 | bool_exp OR bool_exp
			 | NOT  bool_exp
			 | Expressions EQ Expressions | Expressions NOT EQL Expressions | Expressions NEQ Expressions ;

import_stmt : IMPT VAR ;
pass_stmt : PASS;
break_stmt : BREAK;
assign_stmt : VAR EQL Expressions | VAR EQL func_call ;
print_stmt : PRINT OP STR CP ;

finalStatements : basic_stmt | cmpd_stmt | func_def;

cmpd_stmt : if_stmt | while_stmt;

if_stmt : IF bool_exp CLN start_suite elif_stmts;
elif_stmts : | ELIF bool_exp CLN start_suite elif_stmts | else_stmts;
else_stmts : ELSE CLN start_suite;

while_stmt : WHILE bool_exp CLN start_suite; 
start_suite : basic_stmt | NL ID finalStatements suite;
suite : NL ND finalStatements suite | NL end_suite;
end_suite : DD finalStatements | DD | ;

args_list : VAR CM args_list | VAR | ;
func_def : DEF VAR OP args_list CP CLN start_suite;
func_call : VAR OP args_list CP
%%

void yyerror(const char *msg)
{
	printf("Syntax Error at Line %d\n",  yylineno);
	exit(0);
}

int main()
{
	printf("Enter the Expression\n");
	yyparse();
	return 0;
}
