/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CALCULATOR_TAB_H_INCLUDED
# define YY_YY_CALCULATOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WORD = 258,                    /* WORD  */
    ASSIGNMENT_WORD = 259,         /* ASSIGNMENT_WORD  */
    NAME = 260,                    /* NAME  */
    NEWLINE = 261,                 /* NEWLINE  */
    IO_NUMBER = 262,               /* IO_NUMBER  */
    AND_IF = 263,                  /* AND_IF  */
    OR_IF = 264,                   /* OR_IF  */
    DSEMI = 265,                   /* DSEMI  */
    DLESS = 266,                   /* DLESS  */
    DGREAT = 267,                  /* DGREAT  */
    LESSAND = 268,                 /* LESSAND  */
    GREATAND = 269,                /* GREATAND  */
    LESSGREAT = 270,               /* LESSGREAT  */
    DLESSDASH = 271,               /* DLESSDASH  */
    CLOBBER = 272,                 /* CLOBBER  */
    If = 273,                      /* If  */
    Then = 274,                    /* Then  */
    Else = 275,                    /* Else  */
    Elif = 276,                    /* Elif  */
    Fi = 277,                      /* Fi  */
    Do = 278,                      /* Do  */
    Done = 279,                    /* Done  */
    Case = 280,                    /* Case  */
    Esac = 281,                    /* Esac  */
    While = 282,                   /* While  */
    Until = 283,                   /* Until  */
    For = 284,                     /* For  */
    Lbrace = 285,                  /* Lbrace  */
    Rbrace = 286,                  /* Rbrace  */
    Bang = 287,                    /* Bang  */
    In = 288                       /* In  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CALCULATOR_TAB_H_INCLUDED  */
