%{
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
%}

%union { char *text; int depth; struct ASTNode* node;};
%locations
   	  
%token T_EndOfFile T_Return T_Number T_True T_False T_ID T_Print T_Cln T_NL T_EQL T_NEQ T_EQ T_GT T_LT T_EGT T_ELT T_Or T_And T_Not T_In ID ND DD T_String Trip_Quote T_If T_Elif T_While T_Else T_Import T_Break T_Pass T_MN T_PL T_DV T_ML T_OP T_CP T_OB T_CB T_Def T_Comma T_Range T_List

%right T_EQL                                          
%left T_PL T_MN
%left T_ML T_DV
%nonassoc T_If
%nonassoc T_Elif
%nonassoc T_Else

%type<node> StartDebugger args start_suite suite end_suite func_call call_args StartParse finalStatements arith_exp bool_exp term constant basic_stmt cmpd_stmt func_def list_index import_stmt pass_stmt break_stmt print_stmt if_stmt elif_stmts else_stmt while_stmt return_stmt assign_stmt bool_term bool_factor

%%

StartDebugger : {init();} StartParse T_EndOfFile {printf("\nValid Python Syntax\n"); printSTable(); /*printAST($2);*/ codeGenOp($2); printQuads(); freeAll(); exit(0);} ;

constant : T_Number {insertRecord("Constant", $<text>1, @1.first_line, currentScope); $$ = createID_Const("Constant", $<text>1, currentScope);}
         | T_String {insertRecord("Constant", $<text>1, @1.first_line, currentScope); $$ = createID_Const("Constant", $<text>1, currentScope);};

term : T_ID {modifyRecordID("Identifier", $<text>1, @1.first_line, currentScope); $$ = createID_Const("Identifier", $<text>1, currentScope);} 
     | constant {$$ = $1;} 
     | list_index {$$ = $1;};


list_index : T_ID T_OB constant T_CB {checkList($<text>1, @1.first_line, currentScope); $$ = createOp("ListIndex", 2, createID_Const("ListTypeID", $<text>1, currentScope), $3);};

StartParse : T_NL StartParse {$$=$2;}| finalStatements T_NL {resetDepth();} StartParse {$$ = createOp("NewScope", 2, $1, $4);}| finalStatements T_NL {$$=$1;};

basic_stmt : pass_stmt {$$=$1;}
           | break_stmt {$$=$1;}
           | import_stmt {$$=$1;}
           | assign_stmt {$$=$1;}
           | arith_exp {$$=$1;}
           | bool_exp {$$=$1;}
           | print_stmt {$$=$1;}
           | return_stmt {$$=$1;} ; 

arith_exp : term {$$=$1;}
          | arith_exp  T_PL  arith_exp {$$ = createOp("+", 2, $1, $3);}
          | arith_exp  T_MN  arith_exp {$$ = createOp("-", 2, $1, $3);}
          | arith_exp  T_ML  arith_exp {$$ = createOp("*", 2, $1, $3);}
          | arith_exp  T_DV  arith_exp {$$ = createOp("/", 2, $1, $3);}
          | T_OP arith_exp T_CP {$$ = $2;} ;
		    

bool_exp : bool_term T_Or bool_term {$$ = createOp("or", 2, $1, $3);}
         | arith_exp T_LT arith_exp {$$ = createOp("<", 2, $1, $3);}
         | bool_term T_And bool_term {$$ = createOp("and", 2, $1, $3);}
         | arith_exp T_GT arith_exp {$$ = createOp(">", 2, $1, $3);}
         | arith_exp T_ELT arith_exp {$$ = createOp("<=", 2, $1, $3);}
         | arith_exp T_EGT arith_exp {$$ = createOp(">=", 2, $1, $3);}
         | arith_exp T_In T_ID {checkList($<text>3, @3.first_line, currentScope); $$ = createOp("in", 2, $1, createID_Const("Constant", $<text>3, currentScope));}
         | bool_term {$$=$1;}; 

bool_term : bool_factor {$$ = $1;}
          | arith_exp T_EQ arith_exp {$$ = createOp("==", 2, $1, $3);}
          | T_True {insertRecord("Constant", "True", @1.first_line, currentScope); $$ = createID_Const("Constant", "True", currentScope);};
          | T_False {insertRecord("Constant", "False", @1.first_line, currentScope); $$ = createID_Const("Constant", "False", currentScope);}; ;
          
bool_factor : T_Not bool_factor {$$ = createOp("!", 1, $2);}
            | T_OP bool_exp T_CP {$$ = $2;}; 

import_stmt : T_Import T_ID {insertRecord("PackageName", $<text>2, @2.first_line, currentScope); $$ = createOp("import", 1, createID_Const("PackageName", $<text>2, currentScope));};
pass_stmt : T_Pass {$$ = createOp("pass", 0);};
break_stmt : T_Break {$$ = createOp("break", 0);};
return_stmt : T_Return {$$ = createOp("return", 0);};;

assign_stmt : T_ID T_EQL arith_exp {insertRecord("Identifier", $<text>1, @1.first_line, currentScope); $$ = createOp("=", 2, createID_Const("Identifier", $<text>1, currentScope), $3);}  
            | T_ID T_EQL bool_exp {insertRecord("Identifier", $<text>1, @1.first_line, currentScope);$$ = createOp("=", 2, createID_Const("Identifier", $<text>1, currentScope), $3);}   
            | T_ID  T_EQL func_call {insertRecord("Identifier", $<text>1, @1.first_line, currentScope); $$ = createOp("=", 2, createID_Const("Identifier", $<text>1, currentScope), $3);} 
            | T_ID T_EQL T_OB T_CB {insertRecord("ListTypeID", $<text>1, @1.first_line, currentScope); $$ = createID_Const("ListTypeID", $<text>1, currentScope);} ;
	      
print_stmt : T_Print T_OP constant T_CP {$$ = createOp("Print", 1, $3);};

finalStatements : basic_stmt {$$ = $1;}
                | cmpd_stmt {$$ = $1;}
                | func_def {$$ = $1;}
                | func_call {$$ = $1;};

cmpd_stmt : if_stmt {$$ = $1;}
          | while_stmt {$$ = $1;};


if_stmt : T_If bool_exp T_Cln start_suite {$$ = createOp("If", 2, $2, $4);}
        | T_If bool_exp T_Cln start_suite elif_stmts {$$ = createOp("If", 3, $2, $4, $5);};

elif_stmts : else_stmt {$$= $1;}
           | T_Elif bool_exp T_Cln start_suite elif_stmts {$$= createOp("Elif", 3, $2, $4, $5);};

else_stmt : T_Else T_Cln start_suite {$$ = createOp("Else", 1, $3);};

while_stmt : T_While bool_exp T_Cln start_suite {$$ = createOp("While", 2, $2, $4);}; 

start_suite : basic_stmt {$$ = $1;}
            | T_NL ID {initNewTable($<depth>2); updateCScope($<depth>2);} finalStatements suite {$$ = createOp("BeginBlock", 2, $4, $5);};

suite : T_NL ND finalStatements suite {$$ = createOp("Next", 2, $3, $4);}
      | T_NL end_suite {$$ = $2;};

end_suite : DD {updateCScope($<depth>1);} finalStatements {$$ = createOp("EndBlock", 1, $3);} 
          | DD {updateCScope($<depth>1);} {$$ = createOp("EndBlock", 0);}
          | {$$ = createOp("EndBlock", 0); resetDepth();};

args : T_ID {addToList($<text>1, 1);} args_list {$$ = createOp(argsList, 0); clearArgsList();} 
     | {$$ = createOp("Void", 0);};

args_list : T_Comma T_ID {addToList($<text>2, 0);} args_list | ;


call_list : T_Comma term {addToList($<text>1, 0);} call_list | ;

call_args : term {addToList($<text>1, 1);} call_list {$$ = createOp(argsList, 0); clearArgsList();}
					| {$$ = createOp("Void", 0);};

func_def : T_Def T_ID {insertRecord("Func_Name", $<text>2, @2.first_line, currentScope);} T_OP args T_CP T_Cln start_suite {$$ = createOp("Func_Name", 3, createID_Const("Func_Name", $<text>2, currentScope), $5, $8);};

func_call : T_ID T_OP call_args T_CP {$$ = createOp("Func_Call", 2, createID_Const("Func_Name", $<text>1, currentScope), $3);};

 
%%

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

