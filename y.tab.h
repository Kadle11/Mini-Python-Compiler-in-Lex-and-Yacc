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
    T_Number = 259,
    T_True = 260,
    T_False = 261,
    T_ID = 262,
    T_Print = 263,
    T_Cln = 264,
    T_NL = 265,
    T_EQL = 266,
    T_NEQ = 267,
    T_EQ = 268,
    T_GT = 269,
    T_LT = 270,
    T_EGT = 271,
    T_ELT = 272,
    T_Or = 273,
    T_And = 274,
    T_Not = 275,
    ID = 276,
    ND = 277,
    DD = 278,
    T_String = 279,
    Trip_Quote = 280,
    T_If = 281,
    T_Elif = 282,
    T_While = 283,
    T_Else = 284,
    T_Import = 285,
    T_Break = 286,
    T_Pass = 287,
    T_MN = 288,
    T_PL = 289,
    T_DV = 290,
    T_ML = 291,
    T_OP = 292,
    T_CP = 293,
    T_OB = 294,
    T_CB = 295,
    T_Def = 296,
    T_Comma = 297,
    T_Range = 298,
    T_List = 299
  };
#endif
/* Tokens.  */
#define T_EndOfFile 258
#define T_Number 259
#define T_True 260
#define T_False 261
#define T_ID 262
#define T_Print 263
#define T_Cln 264
#define T_NL 265
#define T_EQL 266
#define T_NEQ 267
#define T_EQ 268
#define T_GT 269
#define T_LT 270
#define T_EGT 271
#define T_ELT 272
#define T_Or 273
#define T_And 274
#define T_Not 275
#define ID 276
#define ND 277
#define DD 278
#define T_String 279
#define Trip_Quote 280
#define T_If 281
#define T_Elif 282
#define T_While 283
#define T_Else 284
#define T_Import 285
#define T_Break 286
#define T_Pass 287
#define T_MN 288
#define T_PL 289
#define T_DV 290
#define T_ML 291
#define T_OP 292
#define T_CP 293
#define T_OB 294
#define T_CB 295
#define T_Def 296
#define T_Comma 297
#define T_Range 298
#define T_List 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 190 "grammar.y" /* yacc.c:1909  */
 char *text; int depth; 

#line 145 "y.tab.h" /* yacc.c:1909  */
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
