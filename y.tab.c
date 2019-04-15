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
	#include<stdarg.h>

	
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
    /*Operator*/
    char *NType;
    int noOps;
    struct ASTNode** NextLevel;
    
    /*Identifier or Const*/
    record *id;
	
	} node;
  
  

	STable *symbolTables = NULL;
	int sIndex = -1, aIndex = -1, tabCount = 0;
	node *rootNode;
	char *argsList = NULL;
	
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
	void addToList(char *newVal);
	void clearArgsList();
	
	/*------------------------------------------------------------------------------*/
	
  node *createID_Const(char *type, char *value, int scope)
  {
    node *newNode;
    newNode = (node*)calloc(1, sizeof(node));
    newNode->NType = NULL;
    newNode->noOps = -1;
    newNode->id = findRecord(value, type, scope);
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
    return newNode;
  }
  
  void addToList(char *newVal)
  {
    strcat(argsList, ", ");
    strcat(argsList, newVal);
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
			printf("Identifier '%s' at line %d Not Declared\n", name, yylineno);
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
			printf("Identifier '%s' at line %d Not Declared as an Indexable Type\n", name, yylineno);
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
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					return &(symbolTables[index].Elements[i]);
				}	
			}
			printf("Identifier '%s' at line %d Not Declared\n", name, yylineno);
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
		
		printf("----------------------------All Symbol Tables----------------------------");
		printf("\nScope\tName\tType\t\tDeclaration\tLast Used Line\n");
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				printf("(%d, %d)\t%s\t%s\t%d\t\t%d\n", symbolTables[i].Parent, symbolTables[i].scope, symbolTables[i].Elements[j].name, symbolTables[i].Elements[j].type, symbolTables[i].Elements[j].decLineNo,  symbolTables[i].Elements[j].lastUseLine);
			}
		}
		
		printf("-------------------------------------------------------------------------");
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
	      printf("  ");
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
	
	void freeAll()
	{
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
	}

#line 450 "y.tab.c" /* yacc.c:339  */

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
    ID = 277,
    ND = 278,
    DD = 279,
    T_String = 280,
    Trip_Quote = 281,
    T_If = 282,
    T_Elif = 283,
    T_While = 284,
    T_Else = 285,
    T_Import = 286,
    T_Break = 287,
    T_Pass = 288,
    T_MN = 289,
    T_PL = 290,
    T_DV = 291,
    T_ML = 292,
    T_OP = 293,
    T_CP = 294,
    T_OB = 295,
    T_CB = 296,
    T_Def = 297,
    T_Comma = 298,
    T_Range = 299,
    T_List = 300
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
#define ID 277
#define ND 278
#define DD 279
#define T_String 280
#define Trip_Quote 281
#define T_If 282
#define T_Elif 283
#define T_While 284
#define T_Else 285
#define T_Import 286
#define T_Break 287
#define T_Pass 288
#define T_MN 289
#define T_PL 290
#define T_DV 291
#define T_ML 292
#define T_OP 293
#define T_CP 294
#define T_OB 295
#define T_CB 296
#define T_Def 297
#define T_Comma 298
#define T_Range 299
#define T_List 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 385 "grammar.y" /* yacc.c:355  */
 char *text; int depth; struct ASTNode* node;

#line 583 "y.tab.c" /* yacc.c:355  */
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

#line 614 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   401,   401,   401,   403,   404,   406,   407,   407,   410,
     412,   412,   412,   414,   415,   416,   417,   418,   419,   420,
     421,   423,   424,   425,   426,   427,   428,   431,   432,   433,
     434,   435,   436,   437,   439,   440,   441,   442,   444,   445,
     447,   448,   449,   450,   452,   453,   454,   455,   457,   459,
     460,   461,   463,   464,   467,   468,   470,   471,   473,   475,
     477,   478,   478,   480,   481,   483,   483,   484,   486,   487,
     489,   489,   491,   491,   493
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
  "T_Not", "ID", "ND", "DD", "T_String", "Trip_Quote", "T_If", "T_Elif",
  "T_While", "T_Else", "T_Import", "T_Break", "T_Pass", "T_MN", "T_PL",
  "T_DV", "T_ML", "T_OP", "T_CP", "T_OB", "T_CB", "T_Def", "T_Comma",
  "T_Range", "T_List", "$accept", "StartDebugger", "$@1", "constant",
  "term", "list_index", "StartParse", "$@2", "basic_stmt", "arith_exp",
  "bool_exp", "bool_term", "bool_factor", "import_stmt", "pass_stmt",
  "break_stmt", "return_stmt", "assign_stmt", "print_stmt",
  "finalStatements", "cmpd_stmt", "if_stmt", "elif_stmts", "else_stmt",
  "while_stmt", "start_suite", "$@3", "suite", "end_suite", "$@4", "args",
  "args_list", "func_def", "$@5", "func_call", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -101

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-101)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -101,    12,    65,  -101,  -101,  -101,  -101,  -101,    -4,   -17,
     -15,  -101,   134,   134,    10,  -101,  -101,   134,    17,  -101,
    -101,  -101,    25,  -101,   130,  -101,    19,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,    55,  -101,  -101,  -101,  -101,    94,
      -1,    -1,   134,  -101,     0,   130,    58,    69,  -101,    46,
      45,  -101,  -101,    29,    29,    29,    29,    29,    29,    29,
      29,    29,   134,   134,  -101,   -18,    48,   130,  -101,  -101,
      50,    67,   105,   105,  -101,  -101,    70,    29,    86,    86,
      86,    86,    86,    51,    51,  -101,  -101,    41,  -101,  -101,
      65,   119,  -101,  -101,  -101,   106,  -101,     5,  -101,   119,
     -20,  -101,    88,    90,  -101,   134,   123,  -101,  -101,    96,
     141,  -101,  -101,    65,   140,   105,   142,  -101,   143,   105,
    -101,   105,    81,  -101,     5,  -101,    65,  -101,  -101,  -101,
     143,    65,  -101,  -101
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,    43,     4,    36,    37,     6,     0,
       0,     5,     0,     0,     0,    42,    41,     0,     0,     7,
      21,     8,     0,    49,    17,    18,    33,    34,    15,    13,
      14,    20,    16,    19,    12,    50,    52,    53,    51,     0,
       0,     0,     0,    38,     6,     0,     0,     0,    40,     0,
       0,    72,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     6,     0,    44,    45,    46,
       0,     0,     0,     0,    26,    39,     0,     0,    35,    30,
      28,    32,    31,    23,    22,    25,    24,     0,    27,    29,
       0,    69,    47,     9,    48,     0,    60,    54,    59,    69,
       0,    11,    71,     0,    61,     0,     0,    55,    56,     0,
       0,    68,    74,     0,     0,     0,     0,    70,     0,     0,
      58,     0,    67,    62,     0,    73,     0,    65,    64,    57,
       0,     0,    63,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,  -101,    77,  -101,  -101,    61,  -101,   -63,   -12,
     -10,    62,   146,  -101,  -101,  -101,  -101,  -101,  -101,  -100,
    -101,  -101,    33,  -101,  -101,   -62,  -101,    23,  -101,  -101,
      59,  -101,  -101,  -101,  -101
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    19,    20,    21,    22,    90,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   107,   108,    37,    97,   113,   123,   128,   131,
     103,   111,    38,    76,    69
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      45,    45,    46,    47,     5,    49,    10,    50,    39,    96,
      96,    98,     3,   118,    58,    59,    60,    61,    48,    74,
      91,    41,    40,    42,    11,    51,   130,    67,    52,    68,
      45,   133,    50,   105,     5,   106,    40,    44,    62,    63,
      40,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    87,    96,   120,    11,    53,    96,   124,    96,   125,
      53,    54,    55,    56,    57,   100,    64,    77,    72,     4,
       5,     6,     7,     8,     9,    58,    59,    60,    61,    73,
      58,    59,    60,    61,    75,    74,    10,    60,    61,    92,
      11,    93,    12,    45,    13,   114,    14,    15,    16,     5,
       6,     7,    65,    17,   126,   127,    94,    18,    99,     4,
       5,     6,     7,     8,     9,    10,    95,    70,    71,    11,
      58,    59,    60,    61,    88,    89,    10,   102,   104,   112,
      11,   110,    17,   115,    66,   116,    14,    15,    16,     5,
       6,     7,    44,    17,    53,    54,    55,    56,    57,   117,
     119,   101,   121,   132,   122,    10,    43,   129,   109,    11,
       0,     0,     0,     0,    58,    59,    60,    61,     0,     0,
       0,     0,    17
};

static const yytype_int16 yycheck[] =
{
      12,    13,    12,    13,     5,    17,    21,    17,    12,    72,
      73,    73,     0,   113,    34,    35,    36,    37,     8,    39,
      38,    38,    40,    38,    25,     8,   126,    39,     3,    39,
      42,   131,    42,    28,     5,    30,    40,     8,    19,    20,
      40,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   115,   115,    25,    14,   119,   119,   121,   121,
      14,    15,    16,    17,    18,    77,    11,    38,    10,     4,
       5,     6,     7,     8,     9,    34,    35,    36,    37,    10,
      34,    35,    36,    37,    39,    39,    21,    36,    37,    41,
      25,    41,    27,   105,    29,   105,    31,    32,    33,     5,
       6,     7,     8,    38,    23,    24,    39,    42,    38,     4,
       5,     6,     7,     8,     9,    21,    11,    40,    41,    25,
      34,    35,    36,    37,    62,    63,    21,     8,    22,    39,
      25,    43,    38,    10,    40,    39,    31,    32,    33,     5,
       6,     7,     8,    38,    14,    15,    16,    17,    18,     8,
      10,    90,    10,   130,    11,    21,    10,   124,    99,    25,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     4,     5,     6,     7,     8,     9,
      21,    25,    27,    29,    31,    32,    33,    38,    42,    49,
      50,    51,    52,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    70,    78,    12,
      40,    38,    38,    58,     8,    55,    56,    56,     8,    55,
      56,     8,     3,    14,    15,    16,    17,    18,    34,    35,
      36,    37,    19,    20,    11,     8,    40,    55,    56,    80,
      49,    49,    10,    10,    39,    39,    79,    38,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    57,    57,
      53,    38,    41,    41,    39,    11,    54,    71,    71,    38,
      55,    52,     8,    76,    22,    28,    30,    68,    69,    76,
      43,    77,    39,    72,    56,    10,    39,     8,    65,    10,
      71,    10,    11,    73,    71,    71,    23,    24,    74,    68,
      65,    75,    73,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    48,    47,    49,    49,    50,    50,    50,    51,
      53,    52,    52,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      59,    60,    61,    62,    63,    63,    63,    63,    64,    65,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    70,
      71,    72,    71,    73,    73,    75,    74,    74,    76,    76,
      77,    77,    79,    78,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     4,
       0,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     3,     1,     1,     2,     3,
       2,     1,     1,     1,     3,     3,     3,     4,     4,     1,
       1,     1,     1,     1,     4,     5,     1,     5,     3,     4,
       1,     0,     5,     4,     2,     0,     3,     0,     2,     0,
       2,     0,     0,     8,     4
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
#line 401 "grammar.y" /* yacc.c:1646  */
    {init();}
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 401 "grammar.y" /* yacc.c:1646  */
    {printf("\nValid Python Syntax\n"); printSTable(); printAST((yyvsp[-1].node)); freeAll(); exit(0);}
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 403 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[0].text), currentScope);}
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 404 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[0].text), currentScope);}
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 406 "grammar.y" /* yacc.c:1646  */
    {modifyRecordID("Identifier", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Identifier", (yyvsp[0].text), currentScope);}
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 410 "grammar.y" /* yacc.c:1646  */
    {checkList((yyvsp[-3].text), (yylsp[-3]).first_line, currentScope); (yyval.node) = createOp("ListIndex", 1, (yyvsp[-1].node));}
#line 1924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 412 "grammar.y" /* yacc.c:1646  */
    {resetDepth();}
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 412 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("NewScope", 2, (yyvsp[-3].node), (yyvsp[0].node));}
#line 1936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 412 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 414 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 415 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 416 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 417 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 418 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 419 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1978 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 420 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 421 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 423 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 424 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("+", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 425 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("-", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 426 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("*", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 427 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("/", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 428 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 431 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("or", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 432 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("<", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 433 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("and", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 434 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp(">", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 435 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("<=", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 436 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp(">=", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 437 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 439 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 440 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("==", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 441 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", "True", (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "True", currentScope);}
#line 2086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 442 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Constant", "False", (yylsp[0]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "False", currentScope);}
#line 2092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 444 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("!", 1, (yyvsp[0].node));}
#line 2098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 445 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 447 "grammar.y" /* yacc.c:1646  */
    {insertRecord("PackageName", (yyvsp[0].text), (yylsp[0]).first_line, currentScope); (yyval.node) = createOp("import", 1, createID_Const("PackageName", (yyvsp[0].text), currentScope));}
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 448 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("pass", 0);}
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 449 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("break", 0);}
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 450 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("return", 0);}
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 452 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Identifier", (yyvsp[-2].text), (yylsp[-2]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[-2].text), currentScope), (yyvsp[0].node));}
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 453 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Identifier", (yyvsp[-2].text), (yylsp[-2]).first_line, currentScope);(yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[-2].text), currentScope), (yyvsp[0].node));}
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 454 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Identifier", (yyvsp[-2].text), (yylsp[-2]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[-2].text), currentScope), (yyvsp[0].node));}
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 455 "grammar.y" /* yacc.c:1646  */
    {insertRecord("ListTypeID", (yyvsp[-3].text), (yylsp[-3]).first_line, currentScope); (yyval.node) = createID_Const("ListTypeID", (yyvsp[-3].text), currentScope);}
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 457 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Print", 1, (yyvsp[-1].node));}
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 459 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 460 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 461 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 463 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 464 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 467 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("If", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 468 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("If", 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 470 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)= (yyvsp[0].node);}
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 471 "grammar.y" /* yacc.c:1646  */
    {(yyval.node)= createOp("Elif", 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 473 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Else", 1, (yyvsp[0].node));}
#line 2218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 475 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("While", 2, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 477 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 478 "grammar.y" /* yacc.c:1646  */
    {initNewTable((yyvsp[0].depth)); updateCScope((yyvsp[0].depth));}
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 478 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("BeginBlock", 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 2242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 480 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Next", 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 2248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 481 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 483 "grammar.y" /* yacc.c:1646  */
    {updateCScope((yyvsp[0].depth));}
#line 2260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 483 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("EndBlock", 1, (yyvsp[0].node));}
#line 2266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 484 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("EndBlock", 0);}
#line 2272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 486 "grammar.y" /* yacc.c:1646  */
    {addToList((yyvsp[-1].text)); (yyval.node) = createOp("Arguments", 1, argsList); clearArgsList();}
#line 2278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 487 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp("Void", 0);}
#line 2284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 489 "grammar.y" /* yacc.c:1646  */
    {addToList((yyvsp[-1].text));}
#line 2290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 491 "grammar.y" /* yacc.c:1646  */
    {insertRecord("Func_Name", (yyvsp[0].text), (yylsp[0]).first_line, currentScope);}
#line 2296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 491 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp((yyvsp[-6].text), 2, (yyvsp[-3].node), (yyvsp[0].node));}
#line 2302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 493 "grammar.y" /* yacc.c:1646  */
    {(yyval.node) = createOp((yyvsp[-3].text), 1, (yyvsp[-1].node));}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2312 "y.tab.c" /* yacc.c:1646  */
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
#line 495 "grammar.y" /* yacc.c:1906  */


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

