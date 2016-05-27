%option c++ yyclass="zu_scanner" outfile="zu_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
/* $Id: zu_scanner.l,v 1.20 2016/05/20 14:53:30 ist177974 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "zu_scanner.h"
#include "zu_parser.tab.h"

// don't change this
#define yyerror LexerError
%}

HEXADECIMAL     [0123456789a-fA-F]
HEXNO    [123456789a-fA-F]

%x X_STRING X_COMMENT X_STRING_IGNORE
%%

%{
	set_debug(1);
%}

"#"			return tTYPEINTEGER;
"%"			return tTYPEDOUBLE;
"$"			return tTYPESTRING;

">="        return tGE; 
"<="        return tLE; 
"=="        return tEQ; 
"!="        return tNE; 

"["			return tOPENBRACKET;
"]"			return tCLOSEBRACKET;
":"			return tDOUBLEPOINT;

"<>"		return tCONTINUE;
"><"		return tBREAK;
"!!!"		return tRETURN;
"!"			return tMARK;
"?"			return tQMARK;
"!!"		return tPRINTCOMLINHA;
"&"			return tAND;
"|"			return tOR;
"@"			return tREAD;	 	  


  /* ==========[	 	STRING 			]========== */

\"                     			{yy_push_state(X_STRING); yylval.s = new std::string("");}
<X_STRING>\"           			{yy_pop_state(); return tSTRING;}
<X_STRING>\0		   			{yy_pop_state(); return tSTRING; yy_push_state(X_STRING_IGNORE);}
<X_STRING>\\\"         			*yylval.s += "\"";   
<X_STRING>\\n 		 			;
<X_STRING>\\t 		  			;
<X_STRING>\\r 		  			;
<X_STRING>\\{HEXADECIMAL}   	;
<X_STRING>\\0{HEXNO}         	;
<X_STRING>\\{HEXNO}{HEXADECIMAL}?   *yylval.s += strtol(yytext+1, 0, 16);
<X_STRING>.            				*yylval.s += yytext;


<X_STRING_IGNORE>\"	   		yy_pop_state();
<X_STRING_IGNORE>. 	   		; /*IGNORE*/



  /* ==========[		COMMENTS 		]========== */

"//".*$                             ; /* ignore single line comments */

"/*"                                yy_push_state(X_COMMENT);
<X_COMMENT>"/*"                  	yy_push_state(X_COMMENT);
<X_COMMENT>"*/"                    	yy_pop_state();
<X_COMMENT>.|\n                     ; /* ignore block comments */

  
  /* ==========[		INTEGER 		]========== */

"0x"{HEXADECIMAL}+    		 {yylval.i = strtol(yytext, nullptr, 16); return tINTEGER;}

[1-9][0-9]*|0		 {yylval.i = strtol(yytext,   nullptr, 10); return tINTEGER;}


  /* ==========[		REAL NUMBERS 		]========== */

[0-9]*"."[0-9]+[eE][+-]?[0-9]+       { yylval.d = strtod(yytext, nullptr); return tDOUBLE; }
[0-9]+"."[0-9]*[eE][+-]?[0-9]+       { yylval.d = strtod(yytext, nullptr); return tDOUBLE; }
[0-9]*"."[0-9]+                     { yylval.d = strtod(yytext, nullptr); return tDOUBLE; }
[0-9]+"."[0-9]*                     { yylval.d = strtod(yytext, nullptr); return tDOUBLE; }
[0-9]+[eE][+-]?[0-9]+                { yylval.d = strtod(yytext, nullptr); return tDOUBLE; }

[A-Za-z][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;

[-()<>=+*/%;{}.,]       return *yytext;

[ \t\n]+               ; /* ignore whitespace */

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int zu_scanner::yywrap() { return 1; }
