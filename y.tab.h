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
    T_Number = 258,
    T_True = 259,
    T_False = 260,
    T_ID = 261,
    T_Print = 262,
    T_Cln = 263,
    T_NL = 264,
    T_EQL = 265,
    T_NEQ = 266,
    T_EQ = 267,
    T_GT = 268,
    LT = 269,
    T_EGT = 270,
    T_ELT = 271,
    T_Or = 272,
    T_And = 273,
    T_Not = 274,
    ID = 275,
    ND = 276,
    DD = 277,
    T_String = 278,
    Trip_Quote = 279,
    T_If = 280,
    T_Elif = 281,
    T_While = 282,
    T_Else = 283,
    T_Import = 284,
    T_Break = 285,
    T_Pass = 286,
    T_MN = 287,
    T_PL = 288,
    T_DV = 289,
    T_ML = 290,
    T_OP = 291,
    T_CP = 292,
    T_OB = 293,
    T_CB = 294,
    T_Def = 295,
    T_Comma = 296
  };
#endif
/* Tokens.  */
#define T_Number 258
#define T_True 259
#define T_False 260
#define T_ID 261
#define T_Print 262
#define T_Cln 263
#define T_NL 264
#define T_EQL 265
#define T_NEQ 266
#define T_EQ 267
#define T_GT 268
#define LT 269
#define T_EGT 270
#define T_ELT 271
#define T_Or 272
#define T_And 273
#define T_Not 274
#define ID 275
#define ND 276
#define DD 277
#define T_String 278
#define Trip_Quote 279
#define T_If 280
#define T_Elif 281
#define T_While 282
#define T_Else 283
#define T_Import 284
#define T_Break 285
#define T_Pass 286
#define T_MN 287
#define T_PL 288
#define T_DV 289
#define T_ML 290
#define T_OP 291
#define T_CP 292
#define T_OB 293
#define T_CB 294
#define T_Def 295
#define T_Comma 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 90 "grammar.y" /* yacc.c:1909  */
 char *text; 

#line 139 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
