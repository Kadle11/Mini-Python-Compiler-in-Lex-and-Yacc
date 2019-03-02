%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	extern int yylineno;
	
	typedef struct record
	{
		char *type;
		char *name;
	} record;
	
	record *symbolTable = NULL;
	
	void init()
	{
		symbolTable = (record*)calloc(500, sizeof(record));
		printf("Symbol Table Initialized\n");
	}
	
	int sIndex = -1;
	
	int searchRecord(const char* type, const char *name)
	{
		int i = 0;
		for(i=0; i<=sIndex; i++)
		{
			if((strcmp(symbolTable[i].type, type)==0) && (strcmp(symbolTable[i].name, name)==0))
			{
				return i;
			}
		}
		return -1;
	}
	
	void modifyRecord(int rIndex, const char *type, const char *name)
	{
			strcpy(symbolTable[rIndex].type, type);
			strcpy(symbolTable[rIndex].name, name);	

	}
	void insertRecord(const char* type, const char *name)
	{ 
		int recordIndex = searchRecord(type, name);
		if(recordIndex==-1)
		{
			sIndex++;
			symbolTable[sIndex].type = (char*)calloc(30, sizeof(char));
			symbolTable[sIndex].name = (char*)calloc(20, sizeof(char));
		
			strcpy(symbolTable[sIndex].type, type);	
			strcpy(symbolTable[sIndex].name, name);		
		}
		else
		{
			modifyRecord(recordIndex, type, name);
		}
	}
	
/*	void removeRecord(const char *type, const char *name)
	{
		int recordIndex = searchRecord(type, name);
		
		int i = 0;
		for(i = recordIndex; i <= sIndex; i++)
		{
			strcpy(symbolTable[i].type, symbolTable[i+1].type);
			strcpy(symbolTable[i].name, symbolTable[i+1].name); 
		}
		
		sIndex--;
	}
*/
	void printSTable()
	{
		printf("\n\nSl No.\tSymbol\t\tType\n\n");
		int i = 0;
		for(i=0; i<=sIndex; i++)
		{
			printf("%d\t%s\t\t%s\n", i+1, symbolTable[i].name, symbolTable[i].type);
		}
	}
%}

%union { char *text; };
   	  
%token NUM TR FL VAR SPC PRINT CLN NL EQL L_Paren R_Paren NEQ EQ GT LT EGT ELT OR AND NOT ID ND DD STR Trip_Quote HASH IF ELIF WHILE ELSE IMPT BREAK PASS MN PL DV ML OP CP OB CB DEF CM

%right EQL                                          
%left PL MN
%left ML DV

%%
StartDebugger : {init();} StartParse NL {printf("Valid Python Syntax\n"); printSTable(); exit(0);} ;
constant : NUM {insertRecord("Const", $<text>1);}| STR {insertRecord("Const", $<text>1);} ;
term : VAR {insertRecord("Identifier", $<text>1);}| | constant ;
StartParse : finalStatements ;
Expressions :  arith_exp | bool_exp ;
basic_stmt : pass_stmt | break_stmt | import_stmt | assign_stmt | Expressions | print_stmt;
arith_exp :  term | arith_exp  PL  arith_exp |
			    arith_exp  MN  arith_exp |
			    arith_exp  ML  arith_exp |
			    arith_exp  DV  arith_exp | 
			    OP arith_exp CP ;
ROP : GT | LT | ELT | EGT ;
bool_exp : TR | FL | OP bool_exp CP | arith_exp ROP arith_exp 
			 | bool_exp AND bool_exp
			 | bool_exp OR bool_exp
			 | NOT  bool_exp
			 | Expressions EQ Expressions | Expressions NOT EQL Expressions | Expressions NEQ Expressions ;

import_stmt : IMPT VAR ;
pass_stmt : PASS ;
break_stmt : BREAK ;
assign_stmt : VAR {insertRecord("Identifier", $<text>1);} EQL Expressions | VAR {insertRecord("Identifier", $<text>1);} EQL func_call ;
print_stmt : PRINT OP STR CP ;

finalStatements : basic_stmt | cmpd_stmt | func_def ;

cmpd_stmt : if_stmt | while_stmt ;

if_stmt : IF bool_exp CLN start_suite elif_stmts ;
elif_stmts : | ELIF bool_exp CLN start_suite elif_stmts | else_stmts ;
else_stmts : ELSE CLN start_suite ;

while_stmt : WHILE bool_exp CLN start_suite; 
start_suite : basic_stmt | NL ID finalStatements suite;
suite : NL ND finalStatements suite | NL end_suite;
end_suite : DD finalStatements | ;

args_list : VAR CM args_list | VAR | ;
func_def : DEF VAR {insertRecord("Func_Name", $<text>1);} OP args_list CP CLN start_suite;
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
