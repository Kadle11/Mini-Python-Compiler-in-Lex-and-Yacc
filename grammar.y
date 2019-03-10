%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	extern int yylineno;
	int currentScope = 0, previousScope = 0;
	
	typedef struct record
	{
		char *type;
		char *name;
		int decLineNo;
		int lastUseLine;
	} record;

	typedef struct STable
	{
		int no;
		int noOfElems;
		int scope;
		record *Elements;
		int Parent;
		
	} STable;

	STable *symbolTables = NULL;
	int sIndex = -1;
	
	void updateCScope(int scope)
	{
		currentScope = scope;
	}
	
	int scopeBasedTableSearch(int scope)
	{
		int i = sIndex;
		for(i; i > -1; i--)
		{
			if(symbolTables[i].scope == scope)
			{
				return i;
			}
		}
		return -1;
	}
	void initNewTable(int scope)
	{
		sIndex++;
		symbolTables[sIndex].no = sIndex;
		symbolTables[sIndex].scope = scope;
		symbolTables[sIndex].noOfElems = 0;		
		symbolTables[sIndex].Elements = (record*)calloc(20, sizeof(record));
		
		symbolTables[sIndex].Parent = scopeBasedTableSearch(currentScope); 
	}
	
	void init()
	{
		symbolTables = (STable*)calloc(100, sizeof(STable));
		initNewTable(0);
		
	}
	
	
	int searchRecordInScope(const char* type, const char *name)
	{
		int i =0;
		for(i=0; i<symbolTables[sIndex].noOfElems; i++)
		{
			if(strcmp(symbolTables[sIndex].Elements[i].type, type)==0 && (strcmp(symbolTables[sIndex].Elements[i].name, name)))
			{
				return i;
			}	
		}
		return -1;
	}
		
	void modifyRecordID(const char *type, const char *name, int lineNo, int scope)
	{
		int i =0;
		int index = scopeBasedTableSearch(scope);
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)))
				{
					symbolTables[index].Elements[i].lastUseLine = lineNo;
					return;
				}	
			}
			printf("Identifier '%s' at line %d Not Declared\n", name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[sIndex].Elements[i].name, name)))
			{
				symbolTables[index].Elements[i].lastUseLine = lineNo;
				return;
			}	
		}
		
		return modifyRecordID(type, name, symbolTables[index].Parent, lineNo);
	}
	
	void insertRecord(const char* type, const char *name, int lineNo, int scope)
	{ 
		int recordIndex = searchRecordInScope(type, name);
		int index = scopeBasedTableSearch(scope);
		if(recordIndex==-1)
		{
			
			symbolTables[index].Elements[symbolTables[index].noOfElems].type = (char*)calloc(30, sizeof(char));
			symbolTables[index].Elements[symbolTables[index].noOfElems].name = (char*)calloc(20, sizeof(char));
		
			strcpy(symbolTables[index].Elements[symbolTables[index].noOfElems].type, type);	
			strcpy(symbolTables[index].Elements[symbolTables[index].noOfElems].name, name);
			symbolTables[index].Elements[symbolTables[index].noOfElems].decLineNo = lineNo;
			symbolTables[index].Elements[symbolTables[index].noOfElems].lastUseLine = lineNo;
			symbolTables[index].noOfElems++;

		}
		else
		{
			symbolTables[index].Elements[recordIndex].lastUseLine = lineNo;
		}
	}
	

	void printSTable()
	{
		int i = 0, j = 0;
		printf("Scope\tType\tName\t\tDeclaration\tLast Used Line\n");
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				printf("%d\t%s\t%s\t%d\t\t%d\n", symbolTables[i].scope, symbolTables[i].Elements[j].name, symbolTables[i].Elements[j].type, symbolTables[i].Elements[j].decLineNo,  symbolTables[i].Elements[j].lastUseLine);
			}
		}
	}
%}

%union { char *text; int depth; };
%locations
   	  
%token T_EndOfFile T_Number T_True T_False T_ID T_Print T_Cln T_NL T_EQL T_NEQ T_EQ T_GT LT T_EGT T_ELT T_Or T_And T_Not ID ND DD T_String Trip_Quote T_If T_Elif T_While T_Else T_Import T_Break T_Pass T_MN T_PL T_DV T_ML T_OP T_CP T_OB T_CB T_Def T_Comma T_Range T_List

%right T_EQL                                          
%left T_PL T_MN
%left T_ML T_DV

%%
StartDebugger : {init();} StartParse T_EndOfFile {printf("Valid Python Syntax\n"); printSTable(); exit(0);} ;
constant : T_Number {insertRecord("Constant", $<text>1, @1.first_line, currentScope);}| T_String {insertRecord("Constant", $<text>1, @1.first_line, currentScope);} ;
term : T_ID {modifyRecordID("Identifier", $<text>1, @1.first_line, currentScope);}| | constant ;
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
			 | Expressions T_EQ Expressions | Expressions T_NEQ Expressions ;

import_stmt : T_Import T_ID {insertRecord("Package", $<text>2, @2.first_line, currentScope);};
pass_stmt : T_Pass ;
break_stmt : T_Break ;
assign_stmt : T_ID {insertRecord("Identifier", $<text>1, @1.first_line, currentScope);} T_EQL Expressions | T_ID {insertRecord("Identifier", $<text>1, @1.first_line, currentScope);} T_EQL func_call ;
print_stmt : T_Print T_OP T_String T_CP ;

finalStatements : basic_stmt | cmpd_stmt | func_def;

cmpd_stmt : if_stmt | while_stmt ;

if_stmt : T_If bool_exp T_Cln start_suite elif_stmts ;
elif_stmts : | T_Elif bool_exp T_Cln start_suite elif_stmts | else_stmts ;
else_stmts : T_Else T_Cln start_suite ;

while_stmt : T_While bool_exp T_Cln start_suite; 

start_suite : basic_stmt | T_NL ID {initNewTable($<depth>2); updateCScope($<depth>2);} finalStatements suite;
suite : T_NL ND finalStatements suite | T_NL end_suite;
end_suite : DD {updateCScope($<depth>1);} finalStatements |{updateCScope($<depth>0);};

args_list : T_ID T_Comma args_list | T_ID | ;
func_def : T_Def T_ID {insertRecord("Func_Name", $<text>2, @2.first_line, currentScope);} T_OP args_list T_CP T_Cln start_suite;
func_call : T_ID T_OP args_list T_CP ;
 
%%

void yyerror(const char *msg)
{
	printf("Syntax Error at Line %d, Column : %d\n",  yylineno, yylloc.last_column);
	exit(0);
}

int main()
{
	//printf("Enter the Expression\n");
	yyparse();
	return 0;
}

