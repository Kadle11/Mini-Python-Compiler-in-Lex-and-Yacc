%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	extern int yylineno;
	
	typedef struct record
	{
		char *type;
		char *name;
		int decLineNo;
		int lastUseLine;
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
	
	void modifyRecord(int rIndex, const char *type, const char *name, int lineNo)
	{
			symbolTable[rIndex].lastUseLine = lineNo;
	}
	
	void insertRecord(const char* type, const char *name, int lineNo)
	{ 
		int recordIndex = searchRecord(type, name);
		if(recordIndex==-1)
		{
			sIndex++;
			symbolTable[sIndex].type = (char*)calloc(30, sizeof(char));
			symbolTable[sIndex].name = (char*)calloc(20, sizeof(char));
		
			strcpy(symbolTable[sIndex].type, type);	
			strcpy(symbolTable[sIndex].name, name);
			symbolTable[sIndex].decLineNo = lineNo;
			symbolTable[sIndex].lastUseLine = lineNo;

		}
		else
		{
			modifyRecord(recordIndex, type, name, lineNo);
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
		printf("\n\nSl No.\tSymbol\t\tType\t\tDeclaration Line\tLast Used Line\n\n");
		int i = 0;
		for(i=0; i<=sIndex; i++)
		{
			printf("%d\t%s\t\t%s\t\t%d\t\t%d\n", i+1, symbolTable[i].name, symbolTable[i].type, symbolTable[i].decLineNo, symbolTable[i].lastUseLine);
		}
	}
%}

%union { char *text; };
%locations
   	  
%token T_Number T_True T_False T_ID T_Print T_Cln T_NL T_EQL T_NEQ T_EQ T_GT LT T_EGT T_ELT T_Or T_And T_Not ID ND DD T_String Trip_Quote T_If T_Elif T_While T_Else T_Import T_Break T_Pass T_MN T_PL T_DV T_ML T_OP T_CP T_OB T_CB T_Def T_Comma

%right T_EQL                                          
%left T_PL T_MN
%left T_ML T_DV

%%
StartDebugger : {init();} StartParse T_NL {printf("Valid Python Syntax\n"); printSTable(); exit(0);} ;
constant : T_Number {insertRecord("Constant", $<text>1, @1.first_line);}| T_String {insertRecord("Constant", $<text>1, @1.first_line);} ;
term : T_ID {insertRecord("Identifier", $<text>1, @1.first_line);}| | constant ;
StartParse : finalStatements ;
Expressions :  arith_exp | bool_exp ;
basic_stmt : pass_stmt | break_stmt | import_stmt | assign_stmt | Expressions | print_stmt;
arith_exp :  term | arith_exp  T_PL  arith_exp |
			    arith_exp  T_MN  arith_exp |
			    arith_exp  T_ML  arith_exp |
			    arith_exp  T_DV  arith_exp | 
			    T_OP arith_exp T_CP ;
ROP : T_GT | LT | T_ELT | T_EGT ;
bool_exp : T_True | T_False | T_OP bool_exp T_CP | arith_exp ROP arith_exp 
			 | bool_exp T_And bool_exp
			 | bool_exp T_Or bool_exp
			 | T_Not  bool_exp
			 | Expressions T_EQ Expressions | Expressions T_Not T_EQL Expressions | Expressions T_NEQ Expressions ;

import_stmt : T_Import T_ID ;
pass_stmt : T_Pass ;
break_stmt : T_Break ;
assign_stmt : T_ID {insertRecord("Identifier", $<text>1, @1.first_line);} T_EQL Expressions | T_ID {insertRecord("Identifier", $<text>1, @1.first_line);} T_EQL func_call ;
print_stmt : T_Print T_OP T_String T_CP ;

finalStatements : basic_stmt | cmpd_stmt | func_def ;

cmpd_stmt : if_stmt | while_stmt ;

if_stmt : T_If bool_exp T_Cln start_suite elif_stmts ;
elif_stmts : | T_Elif bool_exp T_Cln start_suite elif_stmts | else_stmts ;
else_stmts : T_Else T_Cln start_suite ;

while_stmt : T_While bool_exp T_Cln start_suite; 
start_suite : basic_stmt | T_NL ID finalStatements suite;
suite : T_NL ND finalStatements suite | T_NL end_suite;
end_suite : DD finalStatements | ;

args_list : T_ID T_Comma args_list | T_ID | ;
func_def : T_Def T_ID {insertRecord("Func_Name", $<text>2, @1.first_line);} T_OP args_list T_CP T_Cln start_suite;
func_call : T_ID T_OP args_list T_CP ;

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

