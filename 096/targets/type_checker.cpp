// $Id: type_checker.cpp,v 1.35 2016/05/20 15:45:11 ist177974 Exp $ -*- c++ -*-
#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void zu::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

void zu::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

//---------------------------------------------------------------------------

inline void zu::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if ((node->argument()->type()->name() != basic_type::TYPE_INT)
    && (node->argument()->type()->name() != basic_type::TYPE_DOUBLE)){
      throw std::string("wrong type in argument of unary expression");
  }

  if(node->argument()->type()->name() == basic_type::TYPE_INT){
    node->type(new basic_type(4, basic_type::TYPE_INT)); 
  }
  
 else{
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }
}

void zu::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {//FIX ME
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT){
      throw std::string("wrong type in argument of unary expression");
  }

  if(node->argument()->type()->name() == basic_type::TYPE_INT){
    node->type(new basic_type(4, basic_type::TYPE_INT)); 
  }
}

//--------------------------------------------------------------------------------------------------------

void zu::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  if(node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_INT){

    node->type(new basic_type(4, basic_type::TYPE_INT));
  }

  else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE
    && node->right()->type()->name() == basic_type::TYPE_DOUBLE){

    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }

  else if((node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_POINTER)
    || (node->right()->type()->name() == basic_type::TYPE_INT
    && node->left()->type()->name() == basic_type::TYPE_POINTER))  {

    node->type(new basic_type(4, basic_type::TYPE_POINTER));
  }

  else if((node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    || (node->right()->type()->name() == basic_type::TYPE_INT
    && node->left()->type()->name() == basic_type::TYPE_DOUBLE))    {

    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }

  else{
    node->type(new basic_type(0, basic_type::TYPE_ERROR));
    throw std::string("wrong type in arguments of binary arithmetic expression");
  }
}

void zu::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  if(node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_INT){

    node->type(new basic_type(4, basic_type::TYPE_INT));
  }

  else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE
    && node->right()->type()->name() == basic_type::TYPE_DOUBLE){

    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }

  else if((node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_POINTER)
    || (node->right()->type()->name() == basic_type::TYPE_INT
    && node->left()->type()->name() == basic_type::TYPE_POINTER))  {

    node->type(new basic_type(4, basic_type::TYPE_POINTER));
  }

  else if((node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    || (node->right()->type()->name() == basic_type::TYPE_INT
    && node->left()->type()->name() == basic_type::TYPE_DOUBLE))    {

    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }

  else if(node->left()->type()->name() == basic_type::TYPE_POINTER
    && node->right()->type()->name() == basic_type::TYPE_POINTER){

    //FIX ME DONT KNOW ABOUT RETURN TYPE
    node->type(new basic_type(8, basic_type::TYPE_POINTER));
  }


  else{
    node->type(new basic_type(0, basic_type::TYPE_ERROR));
    throw std::string("wrong type in arguments of binary arithmetic expression");
  }}

//---------------------------------------------------------------------------------------------------------------

inline void zu::type_checker::processMultiplicativa(cdk::binary_expression_node * const node, int lvl){
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if ((node->left()->type()->name() != basic_type::TYPE_INT)
    && (node->left()->type()->name() != basic_type::TYPE_DOUBLE)){
    throw std::string("wrong type in left argument of binary expression");
  }
  node->right()->accept(this, lvl + 2);
  if ((node->right()->type()->name() != basic_type::TYPE_INT)
    && (node->right()->type()->name() != basic_type::TYPE_DOUBLE)){
    throw std::string("wrong type in right argument of binary expression");
  }
  if(node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_INT){

    node->type(new basic_type(4, basic_type::TYPE_INT));
  }

  else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE
    && node->right()->type()->name() == basic_type::TYPE_DOUBLE){

    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }

  else if((node->left()->type()->name() == basic_type::TYPE_INT
    && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    || (node->right()->type()->name() == basic_type::TYPE_INT
    && node->left()->type()->name() == basic_type::TYPE_DOUBLE))  {

    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }
}

void zu::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processMultiplicativa(node, lvl);
}
void zu::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processMultiplicativa(node, lvl);
}

void zu::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  //SO PARA INTEIROS
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT){
    throw std::string("wrong type in left argument of binary expression");
  }

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT){
    throw std::string("wrong type in right argument of binary expression");
  }

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

//----------------------------------------------------------------------------------------------------------------

inline void zu::type_checker::processComparativa(cdk::binary_expression_node * const node, int lvl){
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if((node->left()->type()->name() != basic_type::TYPE_INT) 
    && (node->left()->type()->name() != basic_type::TYPE_DOUBLE)){
    throw std::string("wrong type in left argument of binary expression");
  }

  node->right()->accept(this, lvl + 2);
  if((node->right()->type()->name() != basic_type::TYPE_INT) 
    && (node->right()->type()->name() != basic_type::TYPE_DOUBLE)){
    throw std::string("wrong type in right argument of binary expression");
  }
  node->type(new basic_type(4, basic_type::TYPE_INT)); //as in C
}

void zu::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processComparativa(node, lvl);
}
void zu::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processComparativa(node, lvl);
}
void zu::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processComparativa(node, lvl);
}
void zu::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processComparativa(node, lvl);
}

//---------------------------------------------------------------------------------------------------------------

inline void zu::type_checker::processLogico(cdk::binary_expression_node * const node, int lvl){
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT){
    throw std::string("wrong type in left argument of binary expression");
  }

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT){
    throw std::string("wrong type in right argument of binary expression");
  }

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_or_node(zu::or_node * const node, int lvl) {
  processLogico(node, lvl);
}
void zu::type_checker::do_and_node(zu::and_node * const node, int lvl) {
  processLogico(node, lvl);
}


//----------------------------------------------------------------------------------------------------------------

inline void zu::type_checker::processIgualdade(cdk::binary_expression_node * const node, int lvl){
    ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if((node->left()->type()->name() != basic_type::TYPE_INT) 
    && (node->left()->type()->name() != basic_type::TYPE_DOUBLE)
    && (node->left()->type()->name() != basic_type::TYPE_POINTER)){

    throw std::string("wrong type in left argument of binary expression");
  }

  node->right()->accept(this, lvl + 2);
  if((node->right()->type()->name() != basic_type::TYPE_INT) 
    && (node->right()->type()->name() != basic_type::TYPE_DOUBLE)
    && (node->right()->type()->name() != basic_type::TYPE_POINTER)) {
    throw std::string("wrong type in right argument of binary expression");
  }
  
  node->type(new basic_type(4, basic_type::TYPE_INT)); //as in C
}

void zu::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processIgualdade(node, lvl);
}

void zu::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processIgualdade(node, lvl);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
}


//---------------------------------------------------------------------------

void zu::type_checker::do_assignment_node(zu::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
   node->lvalue()->accept(this, lvl + 2);
  if (node->lvalue()->type()->name() != basic_type::TYPE_INT 
    && node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE 
    && node->lvalue()->type()->name() != basic_type::TYPE_STRING 
    && node->lvalue()->type()->name() != basic_type::TYPE_POINTER){

      throw std::string("wrong type in left argument of assignment expression");
  }

  node->rvalue()->accept(this, lvl + 2);
  if (node->rvalue()->type()->name() != basic_type::TYPE_INT 
    && node->rvalue()->type()->name() != basic_type::TYPE_DOUBLE 
    && node->rvalue()->type()->name() != basic_type::TYPE_STRING 
    && node->rvalue()->type()->name() != basic_type::TYPE_POINTER
    && node->rvalue()->type()->name() != basic_type::TYPE_UNSPEC){

      throw std::string("wrong type in left argument of assignment expression");
  }

  if(node->lvalue()->type()->name() != basic_type::TYPE_INT &&
     node->rvalue()->type()->name() != basic_type::TYPE_UNSPEC)
    
    node->type(new basic_type(4, basic_type::TYPE_INT));
  
  else if(node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE &&
     node->rvalue()->type()->name() != basic_type::TYPE_UNSPEC)
    
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  
  else if ((node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE) &&
     ((node->rvalue()->type()->name() != basic_type::TYPE_INT) ||
      (node->rvalue()->type()->name() != basic_type::TYPE_DOUBLE)))  {
    
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }
  else if(node->lvalue()->type()->name() != node->rvalue()->type()->name()){
    throw "Types should be equals";
  }
  else{
    node->type(node->lvalue()->type());
  }
}

//---------------------------------------------------------------------------

void zu::type_checker::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void zu::type_checker::do_break_node(zu::break_node * const node, int lvl) {
  //FIXME   dont care about types
  //node->accept(this, lvl + 2);
}

void zu::type_checker::do_continue_node(zu::continue_node * const node, int lvl) {
  //FIXME   dont care about types
 // node->accept(this, lvl + 2);
}

void zu::type_checker::do_return_node(zu::return_node * const node, int lvl) {
  //FIXME   dont care about types
  //node->accept(this, lvl + 2);
}

//void zu::type_checker::do_indicapos_node(zu::indicapos_node * const node, int lvl) {
  //FIXME   wrong node
//}

void zu::type_checker::do_printcomlinha_node(zu::printcomlinha_node * const node, int lvl){
  //FIXME
  node->argument()->accept(this, lvl + 2);

  if (node->argument()->type()->name() == basic_type::TYPE_POINTER)
   throw "It is not possible to print pointers";
  
  //If it is a read it is an integer
  if(node->argument()->type()->name() == basic_type::TYPE_UNSPEC)
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));

}

void zu::type_checker::do_printsemlinha_node(zu::printsemlinha_node * const node, int lvl){
  //FIXME
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_POINTER)
   throw "It is not possible to print pointers";
  
  //If it is a read it is an integer
  if(node->argument()->type()->name() == basic_type::TYPE_UNSPEC)
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_index_node(zu::index_node * const node, int lvl){
  
  ASSERT_UNSPEC;
  node->expression()->accept(this, lvl + 2);

  if(node->expression()->type()->name() != basic_type::TYPE_POINTER){
    throw "Index argument must to be a pointer";
  }
  
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void zu::type_checker::do_index_expression_node(zu::index_expression_node * const node, int lvl){
  //FIXME
  ASSERT_UNSPEC;

  //CHECK THIS
  node->shift()->accept(this, lvl+2);

  if(node->shift()->type()->name() != basic_type::TYPE_INT){
    throw "Argument must be an integer";
  }

  if(node->expression()->type()->name() != basic_type::TYPE_POINTER){
    throw "Expression must be a pointer";
  }

  //CHECK THIS 
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void zu::type_checker::do_malloc_node(zu::malloc_node * const node, int lvl){
  //FIXME -DUVIDAS NA IMPLEMENTACAO DESTE TYPECHECKER

  node->argument()->accept(this, lvl + 2);

  //VERIFICAR ESTA CONDICAO
  if(node->argument()->type()->name() == basic_type::TYPE_UNSPEC){
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
  }

  else if(node->argument()->type()->name() != basic_type::TYPE_INT){
    throw "Argument type must be integer";
  }

  node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_read_node(zu::read_node * const node, int lvl) {
 ASSERT_UNSPEC;
  
 node->type(new basic_type(4, basic_type::TYPE_UNSPEC)); // we do not know the type of the read input
}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void zu::type_checker::do_for_node(zu::for_node * const node, int lvl) {
  //FIXME
  if(node->init() != nullptr){
    node->init()->accept(this, lvl+4);
  }
  
  if(node->condition() != nullptr){
    node->condition()->accept(this, lvl+4);
  }
  
  node->block()->accept(this, lvl + 4);

  if(node->incr() != nullptr){
    node->incr()->accept(this, lvl+4);
  }

  //BLOCK CAN BE EMPTY
}

void zu::type_checker::do_bloco_node(zu::bloco_node * const node, int lvl) {
  //FIXME

  if(node->declarations() != nullptr){
    node->declarations()->accept(this, lvl+2);
  }

  if(node->statements() != nullptr){
    node->statements()->accept(this, lvl+2);
  }
}


void zu::type_checker::do_funcdeclar_node(zu::funcdeclar_node * const node, int lvl){
  //FIXME
  std::vector<basic_type*> args;

  if(node->arguments() != nullptr){
    node->arguments()->accept(this, lvl + 2);
    for(size_t i = 0; i < node->arguments()->size(); i++){
      zu::variable_node *var = (zu::variable_node*) node->arguments()->node(i);
      args.push_back(var->type());
    }
  }

  if(_symtab.find(node->name()) != nullptr){
    throw node->name() + " is already declared";
  }

  else{
    std::shared_ptr<zu::symbol> symbol = std::make_shared<zu::symbol>(node->return_type(), node->name());
    symbol->function_args(args);
    symbol->is_var(false);
    _symtab.insert(node->name(), symbol);
  }
  
}

void zu::type_checker::do_func_call_node(zu::func_call_node * const node, int lvl){
  //FIXME
  ASSERT_UNSPEC;
  std::vector<basic_type*> args;

  if(node->args() != nullptr){
    for(size_t i = 0; i < node->args()->size(); i++){
      cdk::expression_node *var = (cdk::expression_node*) node->args()->node(i);
      args.push_back(var->type());
    }
  }

  std::shared_ptr<zu::symbol> symbol = _symtab.find(node->name());

  if(symbol == nullptr){
        throw node->nome() + " not declared";
  }
  bool defined = symbol->is_defined();
  
  if(!defined){
    throw std::string(node->nome() + " not defined");
  }

  else{
    if(symbol->function_args().size() != args.size()){
      throw "Function declaration has different arguments";
    }

    if(node->args() != nullptr){
      for(size_t i = 0; i < node->args()->size(); i++){
        cdk::expression_node *var = (cdk::expression_node*) node->args()->node(i);
        
        if(var->type()->name() != basic_type::TYPE_INT &&
           args.at(i)->name() != basic_type::TYPE_UNSPEC){ 
          var->type(new basic_type(4, basic_type::TYPE_INT));
          continue;
        }
      
        else if(var->type()->name() != basic_type::TYPE_DOUBLE &&
                args.at(i)->name() != basic_type::TYPE_UNSPEC){
          var->type(new basic_type(8, basic_type::TYPE_DOUBLE));
          continue;
        }
        if(args.at(i)->name() != var->type()->name())
          throw node->name() + " arguments don't match";
      }
    }
    
  }
  node->type(symbol->type());
}

void zu::type_checker::do_variable_node(zu::variable_node * const node, int lvl){
  //FIXME

  std::string name = node->name();
  std::shared_ptr<zu::symbol> symbol = _symtab.find_local(name);
  
  if(symbol == nullptr){
    std::shared_ptr<zu::symbol> new_symbol = std::make_shared<zu::symbol>(node->type(), name);
    _symtab.insert(name, new_symbol);
  }
  else
    throw name + " is already declared";

  if(node->initial_value() != nullptr){
    
    node->initial_value()->accept(this, lvl + 2);
    
    if(node->initial_value()->type()->name() != node->type()->name()){
      
      if((node->type()->name() == basic_type::TYPE_DOUBLE && node->initial_value()->type()->name() == basic_type::TYPE_INT) || 
        (node->type()->name() == basic_type::TYPE_POINTER && node->initial_value()->type()->name() == basic_type::TYPE_INT))
        ;
      else{
        throw "error vars";
      }
    }
  }

    //CONFIRMAR SE E PRECISO VERIFICAR SE A INICIALIZACAO E DO TIPO: INT, DOUBLE OU POINTER
}

void zu::type_checker::do_func_node(zu::func_node * const node, int lvl) {
  //FIXME

  std::vector<basic_type*> args;
  const std::string &id = node->identifier();

  if(node->arguments()!=NULL) {

    node->arguments()->accept(this,lvl+2);
    for (size_t i = 0; i < node->arguments()->size(); i++) {
      zu::variable_node *arg = (zu::variable_node*) node->arguments()->node(i);
      args.push_back(arg->type());
    }
  }

  if(node->default_return() != nullptr){
    
    node->default_return()->accept(this, lvl);
    
    if(node->return_type()->name() == basic_type::TYPE_DOUBLE &&
       node->default_return()->type()->name() == basic_type::TYPE_INT);
   
   else if(node->default_return()->type()->name() != node->return_type()->name())
      throw "Return types does not match";
  }

  std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
  if(symbol != nullptr){

    if(symbol->is_defined()){
      throw node->name() + " already defined";
    }

    if(symbol->type()->name() != node->return_type()->name()){
        throw id + " already declared with other return type";
    }
    if(symbol->function_args().size() != args.size()) {
        throw id + " already declared with other arguments";
    }

    node->arguments()->accept(this, lvl+4);

    for(size_t i = 0; i < node->arguments()->size(); i++){
      zu::variable_node *var = (zu::variable_node*) node->arguments()->node(i);
      if(args.at(i)->name() != var->type()->name())
        throw id + " already declared with different arguments type";
    }

    symbol->is_defined(true);  //CHECK THIS
    symbol->is_var(false);
  }else{
    std::shared_ptr<zu::symbol> s = std::make_shared<zu::symbol>(node->return_type(), node->name(), true);
    s->is_defined(true);
    s->function_args(args);
    s->is_var(false);
    _symtab.insert(id, symbol);
  }
}

//---------------------------------------------------------------------------

void zu::type_checker::do_if_node(zu::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->block()->accept(this, lvl+4);
}

void zu::type_checker::do_if_else_node(zu::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->thenblock()->accept(this, lvl + 4);
  if(node->elseblock() != nullptr){
    node->elseblock()->accept(this, lvl + 4);
  }
}

void zu::type_checker::do_identifier_node(zu::identifier_node * const node, int lvl){
  const std::string &id = node->identifier();
  std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
  if (symbol == nullptr) {
        throw "type_checker::do_lvalue_node : " + id + " undeclared";
  } else {
        node->type(symbol->type());
  }
}

void zu::type_checker::do_symmetry_node(zu::symmetry_node * const node, int lvl){
  //FIXME
  processUnaryExpression(node, lvl);
}

void zu::type_checker::do_identity_node(zu::identity_node * const node, int lvl){
  //FIXME
  processUnaryExpression(node, lvl);
}

void zu::type_checker::do_address_node(zu::address_node * const node, int lvl){
  //FIXME
  node->argument()->accept(this, lvl + 2);

  const std::string &id = node->argument()->name();
  std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
  if(symbol == nullptr){
    throw id + " is not declared";
  }

  node->type(new basic_type(4, basic_type::TYPE_INT));
}