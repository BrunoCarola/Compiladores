%{
// $Id: zu_parser.y,v 1.25 2016/05/20 14:53:30 ist177974 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {  
  double                d;  /* real value */
  int                   i;	/* integer value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  zu::lvalue_node      *lvalue;
  basic_type           *type; 
  cdk::string_node     *strnode;
  zu::bloco_node       *bloco;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING


%token  tIF tREAD tBREAK tCONTINUE tRETURN tPRINTCOMLINHA tMARK tOR tAND tTYPEINTEGER tTYPESTRING tTYPEDOUBLE tQMARK tOPENBRACKET tCLOSEBRACKET tDOUBLEPOINT

%nonassoc tIFX
%nonassoc tELSE
%nonassoc tINTEGER tDOUBLE tIDENTIFIER tSTRING
%right '='
%nonassoc tPRINTCOMLINHA tREAD
%left tOR tAND
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc tUNARY '~'
%nonassoc tBREAK tCONTINUE tRETURN tTYPEINTEGER tTYPESTRING tTYPEDOUBLE tDOUBLEPOINT
%right '}' ')' tCLOSEBRACKET
%left '{' '(' tOPENBRACKET


%type <node> instruction var decl func funcvar else instrvar 
%type <sequence> instructions vars decls funcvars exprs instrsvar
%type <expression> expr literal expr_value
%type <lvalue> lval
%type <bloco> bloco
%type <strnode> strnode
%type <type> type
%type <s> string


%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

program: decls  {compiler ->ast($1);}
       ; 

decls : decl             { $$ = new cdk::sequence_node(LINE, $1); }
      | decls decl       { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ; 

decl : var ';'           { $$ = $1; }
     | func              { $$ = $1; }
     ;

vars : var               { $$ = new cdk::sequence_node(LINE, $1); }
     | vars ',' var      { $$ = new cdk::sequence_node(LINE, $3, $1); }
     |                   { $$ = nullptr; }
     ;

var : type tIDENTIFIER                 {$$ = new zu::variable_node(LINE, $1, $2);}
    | type tIDENTIFIER tMARK           {$$ = new zu::variable_node(LINE, $1, $2, nullptr, true);}
    | type tIDENTIFIER tQMARK          {$$ = new zu::variable_node(LINE, $1, $2, nullptr, false, true);}
    | type tIDENTIFIER '=' expr        {$$ = new zu::variable_node(LINE, $1, $2, $4);}
    | type tIDENTIFIER tMARK '=' expr  {$$ = new zu::variable_node(LINE, $1, $2, $5, true); }
    ;

func : type tIDENTIFIER '(' vars ')'                           { $$ = new zu::funcdeclar_node(LINE, $2, $4, $1, false, false);}
     | type tIDENTIFIER tMARK '(' vars ')'                     { $$ = new zu::funcdeclar_node(LINE, $2, $5, $1, true);}
     | tMARK tIDENTIFIER '(' vars ')'                          { $$ = new zu::funcdeclar_node(LINE, $2, $4, nullptr, false, false);}
     | type tIDENTIFIER tQMARK '(' vars ')'                    { $$ = new zu::funcdeclar_node(LINE, $2, $5, $1, false, true);}
     | tMARK tIDENTIFIER tMARK '(' vars ')'                    { $$ = new zu::funcdeclar_node(LINE, $2, $5, nullptr, true, false);}
     | tMARK tIDENTIFIER tQMARK '(' vars ')'                   { $$ = new zu::funcdeclar_node(LINE, nullptr, $5, nullptr, false, true);}
     | type tIDENTIFIER '(' vars ')' bloco                     { $$ = new zu::func_node(LINE, $1, $2, $4, nullptr, $6, false);} 
     | type tIDENTIFIER '(' vars ')' '=' literal bloco         { $$ = new zu::func_node(LINE, $1, $2, $4, $7, $8, false);}
     | type tIDENTIFIER tMARK '(' vars ')' '=' literal bloco   { $$ = new zu::func_node(LINE, $1, $2, $5, $8, $9, true);}
     | type tIDENTIFIER tMARK '(' vars ')' bloco               { $$ = new zu::func_node(LINE, $1, $2, $5, nullptr, $7, true);}
     | tMARK tIDENTIFIER '(' vars ')' bloco                    { $$ = new zu::func_node(LINE, nullptr, $2, $4, nullptr, $6, false);} 
     | tMARK tIDENTIFIER tMARK '(' vars ')' bloco              { $$ = new zu::func_node(LINE, nullptr, $2, $5, nullptr, $7, true);} 
     ; 

bloco : '{' '}'                            { $$ = new zu::bloco_node(LINE); }
      | '{' instructions '}'               { $$ = new zu::bloco_node(LINE, nullptr, $2); }
      | '{' funcvars '}'                   { $$ = new zu::bloco_node(LINE, $2); }
      | '{' funcvars instructions '}'      { $$ = new zu::bloco_node(LINE, $2, $3);}
      ;

funcvars : funcvar            { $$ = new cdk::sequence_node(LINE, $1);}
         | funcvars funcvar   { $$ = new cdk::sequence_node(LINE, $2, $1);}
         ;

funcvar : type tIDENTIFIER ';'            { $$ = new zu::variable_node(LINE, $1, $2);}
        | type tIDENTIFIER '=' expr ';'   { $$ = new zu::variable_node(LINE, $1, $2, $4);}
        ;

instructions : instruction                   { $$ = new cdk::sequence_node(LINE, $1); }
             | instructions instruction      { $$ = new cdk::sequence_node(LINE, $2, $1); }
             ;

instruction : expr ';'                                                       {$$ = new zu::evaluation_node(LINE, $1); }
     | expr tPRINTCOMLINHA                                {$$ = new zu::printcomlinha_node(LINE, $1);}
     | expr tMARK                                         {$$ = new zu::printsemlinha_node(LINE, $1);}
     | tOPENBRACKET expr tCLOSEBRACKET '#' instruction                       {$$ = new zu::if_node(LINE, $2, $5);}
     | tOPENBRACKET expr tCLOSEBRACKET tQMARK instruction else              {$$ = new zu:: if_else_node(LINE, $2, $5, $6);}
     | tOPENBRACKET exprs ';' exprs ';' exprs tCLOSEBRACKET instruction      {$$ = new zu::for_node(LINE, $2, $4, $6, $8); }
     | tOPENBRACKET instrsvar ';' exprs ';' exprs tCLOSEBRACKET instruction       {$$ = new zu::for_node(LINE, $2, $4, $6, $8); }
     | tBREAK                                                                {$$ = new zu::break_node(LINE); }
     | tCONTINUE                                          {$$ = new zu::continue_node(LINE); }
     | tRETURN                                            {$$ = new zu::return_node(LINE); }
     | bloco                                              {$$ = $1;}
     ;

else : tDOUBLEPOINT instruction      {$$ = $2;}
     | %prec tIFX                    {$$ = nullptr;}
     ;

type : '<' type '>'         { $$ = new basic_type(4, basic_type::TYPE_POINTER);}
     | tTYPEINTEGER         { $$ = new basic_type(4, basic_type::TYPE_INT); }
     | tTYPEDOUBLE          { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
     | tTYPESTRING          { $$ = new basic_type(4, basic_type::TYPE_STRING); }
     ;

instrvar : type tIDENTIFIER               {$$ = new zu::variable_node(LINE, $1, $2);}
         | type tIDENTIFIER '=' expr      {$$ = new zu::variable_node(LINE, $1, $2, $4);}
         ;

instrsvar : instrvar                 { $$ = new cdk::sequence_node(LINE, $1); }
          | instrsvar ',' instrvar   { $$ = new cdk::sequence_node(LINE, $3, $1); }
          ;  

exprs : expr             { $$ = new cdk::sequence_node(LINE, $1); }
      | exprs ',' expr   { $$ = new cdk::sequence_node(LINE, $3, $1); }
      |                  { $$ = nullptr;}
      ;

literal : tINTEGER    { $$ = new cdk::integer_node(LINE, $1); }
        | tDOUBLE     { $$ = new cdk::double_node(LINE, $1); }
        | strnode     { $$ = $1; }
        ;

expr : literal                            { $$ = $1;}
     | lval tQMARK                        { $$ = new zu::address_node(LINE, $1); }
     | '~' expr                           { $$ = new cdk::neg_node(LINE, $2); }
     | expr tAND expr                     { $$ = new zu::and_node(LINE, $1, $3); }
     | expr tOR expr                      { $$ = new zu::or_node(LINE, $1, $3); }
     | expr_value                         { $$ = $1;}
     | expr '<' expr                      { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr                      { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr                      { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr                      { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr                      { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr                      { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'                       { $$ = $2; }
     | lval '=' expr                      { $$ = new zu::assignment_node(LINE, $1, $3); }
     | tOPENBRACKET expr tCLOSEBRACKET    { $$ = new zu::malloc_node(LINE, $2); }
     | tREAD                              { $$ = new zu::read_node(LINE); }
     | tIDENTIFIER '(' exprs ')'          { $$ = new zu::func_call_node(LINE, $1, $3); }
     ;    

expr_value : lval                               { $$ = new zu::rvalue_node(LINE, $1); } 
           | expr tTYPEDOUBLE expr              { $$ = new cdk::mod_node(LINE, $1, $3); }
           | '+' expr %prec tUNARY              { $$ = new zu::identity_node(LINE, $2); }
           | '-' expr %prec tUNARY              { $$ = new zu::symmetry_node(LINE, $2); }
           | expr '+' expr                      { $$ = new cdk::add_node(LINE, $1, $3); }
           | expr '-' expr                      { $$ = new cdk::sub_node(LINE, $1, $3); }
           | expr '*' expr                      { $$ = new cdk::mul_node(LINE, $1, $3); }
           | expr '/' expr                      { $$ = new cdk::div_node(LINE, $1, $3); }
           ;

lval : tIDENTIFIER                                 { $$ = new zu::identifier_node(LINE, $1); }
     | expr tOPENBRACKET tINTEGER tCLOSEBRACKET    { $$ = new zu::index_node(LINE, $1, $3); }
     | expr tOPENBRACKET expr tCLOSEBRACKET    { $$ = new zu::index_expression_node(LINE, $1, $3); }
     ;

strnode : string             { $$ = new cdk::string_node(LINE, $1); }
        ;

string : tSTRING             { $$ = $1; }
       | string tSTRING      { $$ = new std::string(*$1 + *$2); delete $1; delete $2; }
       ;

%%
