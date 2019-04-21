/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdarg.h>

	
	extern int yylineno;
	extern int depth;
	extern int top();
	extern int pop();
	int currentScope = 1, previousScope = 1;
	
	int *arrayScope = NULL;
	
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
	
	typedef struct ASTNode
	{
		int nodeNo;
    /*Operator*/
    char *NType;
    int noOps;
    struct ASTNode** NextLevel;
    
    /*Identifier or Const*/
    record *id;
	
	} node;
  
	typedef struct Quad
	{
		char *R;
		char *A1;
		char *A2;
		char *Op;
	} Quad;
	
	STable *symbolTables = NULL;
	int sIndex = -1, aIndex = -1, tabCount = 0, tIndex = 0 , lIndex = 0, qIndex = 0, nodeCount = 0;
	node *rootNode;
	char *argsList = NULL;
	char *tString = NULL, *lString = NULL;
	Quad *allQ = NULL;
	
	/*-----------------------------Declarations----------------------------------*/
	
	record* findRecord(const char *name, const char *type, int scope);
  node *createID_Const(char *value, char *type, int scope);
  int power(int base, int exp);
  void updateCScope(int scope);
  void resetDepth();
	int scopeBasedTableSearch(int scope);
	void initNewTable(int scope);
	void init();
	int searchRecordInScope(const char* type, const char *name, int index);
	void insertRecord(const char* type, const char *name, int lineNo, int scope);
	int searchRecordInScope(const char* type, const char *name, int index);
	void checkList(const char *name, int lineNo, int scope);
	void printSTable();
	void freeAll();
	void addToList(char *newVal, int flag);
	void clearArgsList();
	int checkIfBinOperator(char *Op);
	/*------------------------------------------------------------------------------*/
	
	void Xitoa(int num, char *str)
	{
		if(str == NULL)
		{
			 printf("Allocate Memory\n");
		   return;
		}
		sprintf(str, "%d", num);
	}

	
	char *makeStr(int no, int flag)
	{
		char A[10];
		Xitoa(no, A);
		
		if(flag==1)
		{
				strcpy(tString, "T");
				strcat(tString, A);
				return tString;
		}
		else
		{
				strcpy(lString, "L");
				strcat(lString, A);
				return lString;
		}

	}
	
	void makeQ(char *R, char *A1, char *A2, char *Op)
	{
		
		allQ[qIndex].R = (char*)malloc(strlen(R)+1);
		allQ[qIndex].Op = (char*)malloc(strlen(Op)+1);
		allQ[qIndex].A1 = (char*)malloc(strlen(A1)+1);
		allQ[qIndex].A2 = (char*)malloc(strlen(A2)+1);
		
		strcpy(allQ[qIndex].R, R);
		strcpy(allQ[qIndex].A1, A1);
		strcpy(allQ[qIndex].A2, A2);
		strcpy(allQ[qIndex].Op, Op);
		qIndex++;
		
		return;
	}
	
	int checkIfBinOperator(char *Op)
	{
		if((!strcmp(Op, "+")) || (!strcmp(Op, "*")) || (!strcmp(Op, "-")) || (!strcmp(Op, "/")) || (!strcmp(Op, ">=")) || (!strcmp(Op, "<=")) || (!strcmp(Op, "<")) || (!strcmp(Op, ">")) || 
			 (!strcmp(Op, "in")) || (!strcmp(Op, "==")) || (!strcmp(Op, "and")) || (!strcmp(Op, "or")))
			{
				return 1;
			}
			
			else
			{
				return 0;
			}
	}
	
	void codeGenOp(node *opNode)
	{
		if(opNode == NULL)
		{
			return;
		}
		
		if(opNode->NType == NULL)
		{
			if((!strcmp(opNode->id->type, "Identifier")) || (!strcmp(opNode->id->type, "Constant")))
			{
				printf("T%d = %s\n", opNode->nodeNo, opNode->id->name);
				makeQ(makeStr(opNode->nodeNo, 1), opNode->id->name, "-", "=");
			}
			return;
		}
		
		if((!strcmp(opNode->NType, "If")) || (!strcmp(opNode->NType, "Elif")))
		{			
			switch(opNode->noOps)
			{
				case 2 : 
				{
					int temp = lIndex;
					codeGenOp(opNode->NextLevel[0]);
					printf("If False T%d goto L%d\n", opNode->NextLevel[0]->nodeNo, lIndex);
					makeQ(makeStr(temp, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");
					lIndex++;
					codeGenOp(opNode->NextLevel[1]);
					lIndex--;
					printf("L%d: ", temp);
					makeQ(makeStr(temp, 0), "-", "-", "Label");
					break;
				}
				case 3 : 
				{
					int temp = lIndex;
					codeGenOp(opNode->NextLevel[0]);
					printf("If False T%d goto L%d\n", opNode->NextLevel[0]->nodeNo, lIndex);
					makeQ(makeStr(temp, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");					
					codeGenOp(opNode->NextLevel[1]);
					printf("L%d: ", temp);
					makeQ(makeStr(temp, 0), "-", "-", "Label");
					codeGenOp(opNode->NextLevel[2]);
					lIndex++;
					break;
				}
			}
			return;
		}
		
		if(!strcmp(opNode->NType, "Else"))
		{
			codeGenOp(opNode->NextLevel[0]);
			return;
		}
		
		if(!strcmp(opNode->NType, "While"))
		{
			int temp = lIndex;
			codeGenOp(opNode->NextLevel[0]);
			printf("L%d: If False T%d goto L%d\n", lIndex, opNode->NextLevel[0]->nodeNo, lIndex+1);
			makeQ(makeStr(temp, 0), "-", "-", "Label");		
			makeQ(makeStr(temp+1, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");								
			lIndex+=2;			
			codeGenOp(opNode->NextLevel[1]);
			printf("goto L%d\n", temp);
			makeQ(makeStr(temp, 0), "-", "-", "goto");
			printf("L%d: ", temp+1);
			makeQ(makeStr(temp+1, 0), "-", "-", "Label"); 
			lIndex = lIndex+2;
			return;
		}
		
		if(!strcmp(opNode->NType, "Next"))
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);
			return;
		}
		
		if(!strcmp(opNode->NType, "BeginBlock"))
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);		
			return;	
		}
		
		if(!strcmp(opNode->NType, "EndBlock"))
		{
			switch(opNode->noOps)
			{
				case 0 : 
				{
					break;
				}
				case 1 : 
				{
					codeGenOp(opNode->NextLevel[0]);
					break;
				}
			}
			return;
		}
		
		if(!strcmp(opNode->NType, "ListIndex"))
		{
			printf("T%d = %s[%s]\n", opNode->nodeNo, opNode->NextLevel[0]->id->name, opNode->NextLevel[1]->id->name);
			makeQ(makeStr(opNode->nodeNo, 1), opNode->NextLevel[0]->id->name, opNode->NextLevel[1]->id->name, "=[]");
			return;
		}
		
		if(checkIfBinOperator(opNode->NType)==1)
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);
			printf("T%d = T%d %s T%d\n", opNode->nodeNo, opNode->NextLevel[0]->nodeNo, opNode->NType, opNode->NextLevel[1]->nodeNo);
			makeQ(makeStr(opNode->nodeNo, 1), makeStr(opNode->NextLevel[0]->nodeNo, 1), makeStr(opNode->NextLevel[1]->nodeNo, 1), opNode->NType);
			return;
		}
		
		if(!strcmp(opNode->NType, "import"))
		{
			printf("import %s\n", opNode->NextLevel[0]->id->name);
			makeQ("-", opNode->NextLevel[0]->id->name, "-", "import");
			return;
		}
		
		if(!strcmp(opNode->NType, "NewScope"))
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);
			return;
		}
		
		if(!strcmp(opNode->NType, "="))
		{
			codeGenOp(opNode->NextLevel[1]);
			printf("%s = T%d\n", opNode->NextLevel[0]->id->name, opNode->NextLevel[1]->nodeNo);
			makeQ(opNode->NextLevel[0]->id->name, makeStr(opNode->NextLevel[1]->nodeNo, 1), "-", opNode->NType);
			return;
		}
		
		if(!strcmp(opNode->NType, "Func_Name"))
		{
			printf("Begin Function %s\n", opNode->NextLevel[0]->id->name);
			makeQ("-", opNode->NextLevel[0]->id->name, "-", "BeginF");
			codeGenOp(opNode->NextLevel[2]);
			printf("End Function %s\n", opNode->NextLevel[0]->id->name);
			makeQ("-", opNode->NextLevel[0]->id->name, "-", "EndF");
			return;
		}
		
		if(!strcmp(opNode->NType, "Func_Call"))
		{
			if(!strcmp(opNode->NextLevel[1]->NType, "Void"))
			{
				printf("(T%d)Call Function %s\n", opNode->nodeNo, opNode->NextLevel[0]->id->name);
				makeQ(makeStr(opNode->nodeNo, 1), opNode->NextLevel[0]->id->name, "-", "Call");
			}
			else
			{
				char A[10];
				char* token = strtok(opNode->NextLevel[1]->NType, ","); 
  			int i = 0;
				while (token != NULL) 
				{
						i++; 
				    printf("Push Param %s\n", token);
				    makeQ("-", token, "-", "Param"); 
				    token = strtok(NULL, ","); 
				}
				
				printf("(T%d)Call Function %s, %d\n", opNode->nodeNo, opNode->NextLevel[0]->id->name, i);
				sprintf(A, "%d", i);
				makeQ(makeStr(opNode->nodeNo, 1), opNode->NextLevel[0]->id->name, A, "Call");
				printf("Pop Params for Function %s, %d\n", opNode->NextLevel[0]->id->name, i);
								
				return;
			}
		}		
		
		if(opNode->noOps == 0)
		{
			if(!strcmp(opNode->NType, "break"))
			{
				printf("goto L%d\n", lIndex);
				makeQ(makeStr(lIndex, 0), "-", "-", "goto");
			}

			if(!strcmp(opNode->NType, "pass"))
			{
				makeQ("-", "-", "-", "pass");
			}

			if(!strcmp(opNode->NType, "return"))
			{
				printf("return\n");
				makeQ("-", "-", "-", "return");
			}
		}
		
		
	}
	
  node *createID_Const(char *type, char *value, int scope)
  {
    node *newNode;
    newNode = (node*)calloc(1, sizeof(node));
    newNode->NType = NULL;
    newNode->noOps = -1;
    newNode->id = findRecord(value, type, scope);
    newNode->nodeNo = nodeCount++;
    return newNode;
  }

  node *createOp(char *oper, int noOps, ...)
  {
  
    va_list params;
    node *newNode;
    int i;
    newNode = (node*)calloc(1, sizeof(node));
    
    newNode->NextLevel = (node**)calloc(noOps, sizeof(node*));
    
    newNode->NType = (char*)malloc(strlen(oper)+1);
    strcpy(newNode->NType, oper);
    newNode->noOps = noOps;
    va_start(params, noOps);
    
    for (i = 0; i < noOps; i++)
      newNode->NextLevel[i] = va_arg(params, node*);
    
    va_end(params);
    newNode->nodeNo = nodeCount++;
    return newNode;
  }
  
  void addToList(char *newVal, int flag)
  {
  	if(flag==0)
  	{
		  strcat(argsList, ", ");
		  strcat(argsList, newVal);
		}
		else
		{
			strcat(argsList, newVal);
		}
    //printf("\n\t%s\n", newVal);
  }
  
  void clearArgsList()
  {
    strcpy(argsList, "");
  }
  
	int power(int base, int exp)
	{
		int i =0, res = 1;
		for(i; i<exp; i++)
		{
			res *= base;
		}
		return res;
	}
	
	void updateCScope(int scope)
	{
		currentScope = scope;
	}
	
	void resetDepth()
	{
		while(top()) pop();
		depth = 10;
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
		arrayScope[scope]++;
		sIndex++;
		symbolTables[sIndex].no = sIndex;
		symbolTables[sIndex].scope = power(scope, arrayScope[scope]);
		symbolTables[sIndex].noOfElems = 0;		
		symbolTables[sIndex].Elements = (record*)calloc(20, sizeof(record));
		
		symbolTables[sIndex].Parent = scopeBasedTableSearch(currentScope); 
	}
	
	void init()
	{
		symbolTables = (STable*)calloc(100, sizeof(STable));
		arrayScope = (int*)calloc(10, sizeof(int));
		initNewTable(1);
		argsList = (char *)malloc(100);
		strcpy(argsList, "");
		tString = (char*)calloc(10, sizeof(char));
		lString = (char*)calloc(10, sizeof(char));
		allQ = (Quad*)calloc(1000, sizeof(Quad));
	}

	int searchRecordInScope(const char* type, const char *name, int index)
	{
		int i =0;
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if((strcmp(symbolTables[index].Elements[i].type, type)==0) && (strcmp(symbolTables[index].Elements[i].name, name)==0))
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
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					symbolTables[index].Elements[i].lastUseLine = lineNo;
					return;
				}	
			}
			printf("%s '%s' at line %d Not Declared\n", type, name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				symbolTables[index].Elements[i].lastUseLine = lineNo;
				return;
			}	
		}
		return modifyRecordID(type, name, lineNo, symbolTables[symbolTables[index].Parent].scope);
	}
	
	void insertRecord(const char* type, const char *name, int lineNo, int scope)
	{ 
		int FScope = power(scope, arrayScope[scope]);
		int index = scopeBasedTableSearch(FScope);
		int recordIndex = searchRecordInScope(type, name, index);
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
	
	void checkList(const char *name, int lineNo, int scope)
	{
		int index = scopeBasedTableSearch(scope);
		int i;
		if(index==0)
		{
			
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, "ListTypeID")==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					symbolTables[index].Elements[i].lastUseLine = lineNo;
					return;
				}	

				else if(strcmp(symbolTables[index].Elements[i].name, name)==0)
				{
					printf("Identifier '%s' at line %d Not Indexable\n", name, yylineno);
					exit(1);

				}

			}
			printf("Identifier '%s' at line %d Not Indexable\n", name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, "ListTypeID")==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				symbolTables[index].Elements[i].lastUseLine = lineNo;
				return;
			}
			
			else if(strcmp(symbolTables[index].Elements[i].name, name)==0)
			{
				printf("Identifier '%s' at line %d Not Indexable\n", name, yylineno);
				exit(1);

			}
		}
		
		return checkList(name, lineNo, symbolTables[symbolTables[index].Parent].scope);

	}
	
	record* findRecord(const char *name, const char *type, int scope)
	{
		int i =0;
		int index = scopeBasedTableSearch(scope);
		//printf("FR: %d, %s\n", scope, name);
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					return &(symbolTables[index].Elements[i]);
				}	
			}
			printf("\n%s '%s' at line %d Not Found in Symbol Table\n", type, name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				return &(symbolTables[index].Elements[i]);
			}	
		}
		return findRecord(name, type, symbolTables[symbolTables[index].Parent].scope);
	}

	void printSTable()
	{
		int i = 0, j = 0;
		
		printf("\n----------------------------All Symbol Tables----------------------------");
		printf("\nScope\tName\tType\t\tDeclaration\tLast Used Line\n");
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				printf("(%d, %d)\t%s\t%s\t%d\t\t%d\n", symbolTables[i].Parent, symbolTables[i].scope, symbolTables[i].Elements[j].name, symbolTables[i].Elements[j].type, symbolTables[i].Elements[j].decLineNo,  symbolTables[i].Elements[j].lastUseLine);
			}
		}
		
		printf("-------------------------------------------------------------------------\n");
		
	}
	
	void printAST(node *root)
	{
	  if(root == NULL)
	  {
	    return;
	  }
	  
	  if(root->noOps >= 0)
	  {
	    int i;
	    for(i = 0; i < tabCount; i++)
	    {
	      //printf("  ");
	    }
	    
	    printf("%s\n", root->NType);
	    
	    tabCount++;
	    for(i=0; i < root->noOps; i++)
	    {
	      printAST(root->NextLevel[i]);
	    }
	    tabCount--;
	  }
	  
	  if(root->noOps == -1)
	  {
	    int i = 0;
	    for(i = 0; i < tabCount; i++)
	    {
	      printf("  ");
	    }
	    
	    printf("%s ", root->id->name);
	  }
	  
	  
	}
	
	void printQuads()
	{
		printf("\n--------------------------------All Quads---------------------------------\n");
		int i = 0;
		for(i=0; i<qIndex; i++)
		{
			printf("%s\t%s\t%s\t%s\n", allQ[i].Op, allQ[i].A1, allQ[i].A2, allQ[i].R);
		}
		printf("----------------------------------------------------------------------------\n");
	}
	
	void freeAll()
	{
		printf("\n");
		int i = 0, j = 0;
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				free(symbolTables[i].Elements[j].name);
				free(symbolTables[i].Elements[j].type);	
			}
			free(symbolTables[i].Elements);
		}
		free(symbolTables);
		free(allQ);
	}

#line 756 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_EndOfFile = 258,
    T_Return = 259,
    T_Number = 260,
    T_True = 261,
    T_False = 262,
    T_ID = 263,
    T_Print = 264,
    T_Cln = 265,
    T_NL = 266,
    T_EQL = 267,
    T_NEQ = 268,
    T_EQ = 269,
    T_GT = 270,
    T_LT = 271,
    T_EGT = 272,
    T_ELT = 273,
    T_Or = 274,
    T_And = 275,
    T_Not = 276,
    T_In = 277,
    ID = 278,
    ND = 279,
    DD = 280,
    T_String = 281,
    Trip_Quote = 282,
    T_If = 283,
    T_Elif = 284,
    T_While = 285,
    T_Else = 286,
    T_Import = 287,
    T_Break = 288,
    T_Pass = 289,
    T_MN = 290,
    T_PL = 291,
    T_DV = 292,
    T_ML = 293,
    T_OP = 294,
    T_CP = 295,
    T_OB = 296,
    T_CB = 297,
    T_Def = 298,
    T_Comma = 299,
    T_Range = 300,
    T_List = 301
  };
#endif
/* Tokens.  */
#define T_EndOfFile 258
#define T_Return 259
#define T_Number 260
#define T_True 261
#define T_False 262
#define T_ID 263
#define T_Print 264
#define T_Cln 265
#define T_NL 266
#define T_EQL 267
#define T_NEQ 268
#define T_EQ 269
#define T_GT 270
#define T_LT 271
#define T_EGT 272
#define T_ELT 273
#define T_Or 274
#define T_And 275
#define T_Not 276
#define T_In 277
#define ID 278
#define ND 279
#define DD 280
#define T_String 281
#define Trip_Quote 282
#define T_If 283
#define T_Elif 284
#define T_While 285
#define T_Else 286
#define T_Import 287
#define T_Break 288
#define T_Pass 289
#define T_MN 290
#define T_PL 291
#define T_DV 292
#define T_ML 293
#define T_OP 294
#define T_CP 295
#define T_OB 296
#define T_CB 297
#define T_Def 298
#define T_Comma 299
#define T_Range 300
#define T_List 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 691 "grammar.y" /* yacc.c:355  */
 char *text; int depth; struct ASTNode* node;

#line 891 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 922 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   707,   707,   707,   709,   710,   712,   713,   714,   717,
     719,   719,   719,   719,   721,   722,   723,   724,   725,   726,
     727,   728,   730,   731,   732,   733,   734,   735,   738,   739,
     740,   741,   742,   743,   744,   745,   747,   748,   749,   750,
     752,   753,   755,   756,   757,   758,   760,   761,   762,   763,
     765,   767,   768,   769,   770,   772,   773,   776,   777,   779,
     780,   782,   784,   786,   787,   787,   789,   790,   792,   792,
     793,   793,   794,   796,   796,   797,   799,   799,   799,   802,
     802,   802,   804,   804,   805,   807,   807,   809
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_EndOfFile", "T_Return", "T_Number",
  "T_True", "T_False", "T_ID", "T_Print", "T_Cln", "T_NL", "T_EQL",
  "T_NEQ", "T_EQ", "T_GT", "T_LT", "T_EGT", "T_ELT", "T_Or", "T_And",
  "T_Not", "T_In", "ID", "ND", "DD", "T_String", "Trip_Quote", "T_If",
  "T_Elif", "T_While", "T_Else", "T_Import", "T_Break", "T_Pass", "T_MN",
  "T_PL", "T_DV", "T_ML", "T_OP", "T_CP", "T_OB", "T_CB", "T_Def",
  "T_Comma", "T_Range", "T_List", "$accept", "StartDebugger", "$@1",
  "constant", "term", "list_index", "StartParse", "$@2", "basic_stmt",
  "arith_exp", "bool_exp", "bool_term", "bool_factor", "import_stmt",
  "pass_stmt", "break_stmt", "return_stmt", "assign_stmt", "print_stmt",
  "finalStatements", "cmpd_stmt", "if_stmt", "elif_stmts", "else_stmt",
  "while_stmt", "start_suite", "$@3", "suite", "end_suite", "$@4", "$@5",
  "args", "$@6", "args_list", "$@7", "call_list", "$@8", "call_args",
  "$@9", "func_def", "$@10", "func_call", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF -115

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-115)))

#define YYTABLE_NINF -71

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -115,    20,    73,  -115,  -115,  -115,  -115,  -115,    -2,   -15,
      73,   -12,  -115,    10,    10,    21,  -115,  -115,    10,    26,
    -115,  -115,  -115,    80,  -115,   193,  -115,    55,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,   104,  -115,  -115,  -115,  -115,
    -115,   103,    14,    16,    16,  -115,    10,  -115,    22,   193,
     117,   118,  -115,   166,    83,  -115,  -115,    33,    33,    33,
      33,    33,   124,    33,    33,    33,    33,    10,    10,   130,
     -16,    93,   193,  -115,  -115,  -115,    96,    95,    98,   153,
     153,  -115,  -115,   101,    33,    32,    32,    32,    32,    32,
    -115,    52,    52,  -115,  -115,    50,  -115,  -115,    73,  -115,
     105,  -115,  -115,  -115,     2,   125,  -115,    29,  -115,   142,
      60,  -115,    14,  -115,  -115,    10,   141,  -115,  -115,  -115,
     114,  -115,   113,   143,   153,   111,   155,   105,   152,   153,
    -115,   158,  -115,   153,  -115,    89,  -115,    29,  -115,  -115,
     113,    62,  -115,  -115,   111,   152,   113,  -115,  -115,  -115,
    -115
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,    45,     4,    38,    39,     6,     0,
       0,     0,     5,     0,     0,     0,    44,    43,     0,     0,
       7,    22,     8,     0,    51,    18,    19,    35,    36,    16,
      14,    15,    21,    17,    20,     0,    52,    55,    56,    53,
      54,     0,    84,     0,     0,    10,     0,    40,     6,     0,
       0,     0,    42,     0,     0,    85,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       6,     0,    46,    47,    48,    82,     0,     0,     0,     0,
       0,    27,    41,     0,     0,    37,    31,    29,    33,    32,
      34,    24,    23,    26,    25,     0,    28,    30,     0,    49,
      81,    87,     9,    50,     6,     0,    63,    57,    62,    75,
       0,    12,     0,    83,    64,     0,     0,    58,    59,    73,
       0,    79,     0,     0,     0,    78,     0,    81,     0,     0,
      61,     0,    74,     0,    80,    72,    65,     0,    76,    86,
       0,    68,    67,    60,    78,     0,     0,    71,    77,    66,
      69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,  -115,    82,   -36,  -115,    -6,  -115,   -68,   -13,
     -11,    63,   156,  -115,  -115,  -115,  -115,  -115,  -115,  -114,
    -115,  -115,    31,  -115,  -115,   -67,  -115,    24,  -115,  -115,
    -115,  -115,  -115,    27,  -115,    43,  -115,  -115,  -115,  -115,
    -115,   131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    20,    21,    22,    23,    98,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   117,   118,    38,   107,   122,   136,   142,   146,
     147,   120,   125,   132,   144,   113,   127,    76,   100,    39,
      83,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    49,    50,    51,    45,    53,    75,    54,   128,    11,
      41,   106,   106,   108,    41,     5,     6,     7,    48,     5,
       3,     5,    48,    42,    44,    43,   145,    46,    72,    52,
      73,    11,   150,    49,    55,    54,    12,    42,     5,    43,
      12,    48,    12,    43,    85,    86,    87,    88,    89,    18,
      91,    92,    93,    94,    95,    95,   106,   130,   115,    12,
     116,   106,   137,    43,    57,   106,   139,    63,    64,    65,
      66,   110,    84,   -70,    67,    68,   121,     4,     5,     6,
       7,     8,     9,    56,    10,    63,    64,    65,    66,    65,
      66,   -70,   111,   -70,    11,    63,    64,    65,    66,    12,
      81,    13,    49,    14,   123,    15,    16,    17,     5,     6,
       7,    70,    18,   140,   141,    69,    19,     4,     5,     6,
       7,     8,     9,    82,    11,    77,    78,    79,    80,    12,
      96,    97,    90,   -13,    11,    99,   101,   102,   103,    12,
     109,    13,    18,    14,    71,    15,    16,    17,   114,   112,
     119,   124,    18,   129,   126,   131,    19,     4,     5,     6,
       7,   104,     9,   135,   105,   133,   138,    47,   143,   149,
     134,   148,    74,     0,    11,     0,     0,     0,     0,    12,
      57,    58,    59,    60,    61,    15,    16,    17,    62,     0,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    64,    65,    66,     0,    81,    57,    58,    59,
      60,    61,     0,     0,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,    64,
      65,    66
};

static const yytype_int16 yycheck[] =
{
      13,    14,    13,    14,    10,    18,    42,    18,   122,    21,
      12,    79,    80,    80,    12,     5,     6,     7,     8,     5,
       0,     5,     8,    39,    39,    41,   140,    39,    41,     8,
      41,    21,   146,    46,     8,    46,    26,    39,     5,    41,
      26,     8,    26,    41,    57,    58,    59,    60,    61,    39,
      63,    64,    65,    66,    67,    68,   124,   124,    29,    26,
      31,   129,   129,    41,    14,   133,   133,    35,    36,    37,
      38,    84,    39,    11,    19,    20,   112,     4,     5,     6,
       7,     8,     9,     3,    11,    35,    36,    37,    38,    37,
      38,    29,    98,    31,    21,    35,    36,    37,    38,    26,
      40,    28,   115,    30,   115,    32,    33,    34,     5,     6,
       7,     8,    39,    24,    25,    11,    43,     4,     5,     6,
       7,     8,     9,    40,    21,    43,    44,    10,    10,    26,
      67,    68,     8,     3,    21,    42,    40,    42,    40,    26,
      39,    28,    39,    30,    41,    32,    33,    34,    23,    44,
       8,    10,    39,    10,    40,    44,    43,     4,     5,     6,
       7,     8,     9,    11,    11,    10,     8,    11,   137,   145,
     127,   144,    41,    -1,    21,    -1,    -1,    -1,    -1,    26,
      14,    15,    16,    17,    18,    32,    33,    34,    22,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,     4,     5,     6,     7,     8,     9,
      11,    21,    26,    28,    30,    32,    33,    34,    39,    43,
      50,    51,    52,    53,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    71,    86,
      88,    12,    39,    41,    39,    53,    39,    59,     8,    56,
      57,    57,     8,    56,    57,     8,     3,    14,    15,    16,
      17,    18,    22,    35,    36,    37,    38,    19,    20,    11,
       8,    41,    56,    57,    88,    51,    84,    50,    50,    10,
      10,    40,    40,    87,    39,    56,    56,    56,    56,    56,
       8,    56,    56,    56,    56,    56,    58,    58,    54,    42,
      85,    40,    42,    40,     8,    11,    55,    72,    72,    39,
      56,    53,    44,    82,    23,    29,    31,    69,    70,     8,
      78,    51,    73,    57,    10,    79,    40,    83,    66,    10,
      72,    44,    80,    10,    82,    11,    74,    72,     8,    72,
      24,    25,    75,    69,    81,    66,    76,    77,    80,    74,
      66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    49,    48,    50,    50,    51,    51,    51,    52,
      53,    54,    53,    53,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    60,    61,    62,    63,    64,    64,    64,    64,
      65,    66,    66,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    71,    72,    73,    72,    74,    74,    76,    75,
      77,    75,    75,    79,    78,    78,    81,    80,    80,    83,
      82,    82,    85,    84,    84,    87,    86,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     4,
       2,     0,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     3,     1,     1,
       2,     3,     2,     1,     1,     1,     3,     3,     3,     4,
       4,     1,     1,     1,     1,     1,     1,     4,     5,     1,
       5,     3,     4,     1,     0,     5,     4,     2,     0,     3,
       0,     2,     0,     0,     3,     0,     0,     4,     0,     0,
       4,     0,     0,     3,     0,     0,     8,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 707 "grammar.y" /* yacc.c:1646  */
    {init();}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 707 "grammar.y" /* yacc.c:1646  */
    {printf("\nValid Python Syntax\n"); printSTable(); /*printAST($2);*/ codeGenOp((yyvsp[-1].node)); printQuads(); freeAll(); exit(0);}
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 709 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[0].text), currentScope);}
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 710 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[0].text), currentScope);}
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 712 "grammar.y" /* yacc.c:1646  */
    {modifyRecordID("Identifier", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Identifier", (yyvsp[0].text), currentScope);}
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 713 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 714 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 717 "grammar.y" /* yacc.c:1646  */
    {checkList((yyvsp[-3].text), (yylsp[-3]).first_line, currentScope); (yyval.node) = createOp("ListIndex", 2, createID_Const("ListTypeID", (yyvsp[-3].text), currentScope), (yyvsp[-1].node));}
#line 2268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 719 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 719 "grammar.y" /* yacc.c:1646  */
    {resetDepth();}
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 719 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("NewScope", 2, (yyvsp[-3].node), (yyvsp[0].node));}
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 719 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[-1].node);}
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 721 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 722 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2304 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 723 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 724 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2316 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 725 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2322 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 726 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 727 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 728 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 730 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 731 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("+", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2352 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 732 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("-", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 733 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("*", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2364 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 734 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("/", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 735 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 2376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 738 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("or", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 739 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("<", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 740 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("and", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 741 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp(">", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 742 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("<=", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 743 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp(">=", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 744 "grammar.y" /* yacc.c:1646  */
    {checkList((yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createOp("in", 2, (yyvsp[-2].node), createID_Const("Constant", (yyvsp[0].text), currentScope));}
#line 2418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 745 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 747 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 748 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("==", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 749 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", "True", (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "True", currentScope);}
#line 2442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 750 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", "False", (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "False", currentScope);}
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 752 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("!", 1, (yyvsp[0].node));}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 753 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 2460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 755 "grammar.y" /* yacc.c:1646  */
    {insertRecord("PackageName", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createOp("import", 1, createID_Const("PackageName", (yyvsp[0].text), currentScope));}
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 756 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("pass", 0);}
#line 2472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 757 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("break", 0);}
#line 2478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 758 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("return", 0);}
#line 2484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 760 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Identifier", (yyvsp[-2].text), (yylsp[-2]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[-2].text), currentScope), (yyvsp[0].node));}
#line 2490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 761 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Identifier", (yyvsp[-2].text), (yylsp[-2]).first_line, currentScope);(yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[-2].text), currentScope), (yyvsp[0].node));}
#line 2496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 762 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Identifier", (yyvsp[-2].text), (yylsp[-2]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[-2].text), currentScope), (yyvsp[0].node));}
#line 2502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 763 "grammar.y" /* yacc.c:1646  */
    {insertRecord("ListTypeID", (yyvsp[-3].text), (yylsp[-3]).first_line, currentScope); (yyval.node) = createID_Const("ListTypeID", (yyvsp[-3].text), currentScope);}
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 765 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Print", 1, (yyvsp[-1].node));}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 767 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 768 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 769 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 770 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 772 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 773 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 776 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("If", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 777 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("If", 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 779 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)= (yyvsp[0].node);}
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 780 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)= createOp("Elif", 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 2574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 782 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Else", 1, (yyvsp[0].node));}
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 784 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("While", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 786 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 787 "grammar.y" /* yacc.c:1646  */
    {initNewTable((yyvsp[0].depth)); updateCScope((yyvsp[0].depth));}
#line 2598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 787 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("BeginBlock", 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 2604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 789 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Next", 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 2610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 790 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 792 "grammar.y" /* yacc.c:1646  */
    {updateCScope((yyvsp[0].depth));}
#line 2622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 792 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("EndBlock", 1, (yyvsp[0].node));}
#line 2628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 793 "grammar.y" /* yacc.c:1646  */
    {updateCScope((yyvsp[0].depth));}
#line 2634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 793 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("EndBlock", 0);}
#line 2640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 794 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("EndBlock", 0); resetDepth();}
#line 2646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 796 "grammar.y" /* yacc.c:1646  */
    {addToList((yyvsp[0].text), 1);}
#line 2652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 796 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp(argsList, 0); clearArgsList();}
#line 2658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 797 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Void", 0);}
#line 2664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 799 "grammar.y" /* yacc.c:1646  */
    {addToList((yyvsp[0].text), 0);}
#line 2670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 802 "grammar.y" /* yacc.c:1646  */
    {addToList((yyvsp[-1].text), 0);}
#line 2676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 804 "grammar.y" /* yacc.c:1646  */
    {addToList((yyvsp[0].text), 1);}
#line 2682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 804 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp(argsList, 0); clearArgsList();}
#line 2688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 805 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Void", 0);}
#line 2694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 807 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Func_Name", (yyvsp[0].text), (yylsp[0]).first_line, currentScope);}
#line 2700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 807 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Func_Name", 3, createID_Const("Func_Name", (yyvsp[-6].text), currentScope), (yyvsp[-3].node), (yyvsp[0].node));}
#line 2706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 809 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Func_Call", 2, createID_Const("Func_Name", (yyvsp[-3].text), currentScope), (yyvsp[-1].node));}
#line 2712 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2716 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 812 "grammar.y" /* yacc.c:1906  */


void yyerror(const char *msg)
{
	printf("\nSyntax Error at Line %d, Column : %d\n",  yylineno, yylloc.last_column);
	exit(0);
}

int main()
{
	//printf("Enter the Expression\n");
	yyparse();
	return 0;
}

