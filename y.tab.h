/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 536 "grammar.y" /* yacc.c:1909  */
 char *text; int depth; struct ASTNode* node;

#line 149 "y.tab.h" /* yacc.c:1909  */
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
