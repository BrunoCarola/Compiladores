// $Id: postfix_writer.cpp,v 1.29 2016/05/20 15:45:10 ist177974 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/size_zu.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void zu::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);

  _pf.INT(node->value()); // push an integer
}

void zu::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  int lbl1;

  // generate the string 
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters

  //leave the address on the stack 
  if(_current_function != nullptr){  
    _pf.TEXT(); // return to the TEXT segment
    _pf.ADDR(mklbl(lbl1)); // the string to be printed
  } else {
    // global scope
    _pf.ALIGN();
    _pf.LABEL(*_current_id); 
    _pf.ID(mklbl(lbl1));
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
   CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); 
  _pf.NEG();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);

  if (is_pointer(node->type())) {
    
    _pf.INT(4); // pointer size
    _pf.MUL(); // pointer arithmetics shift calculation
    _pf.ADD();
      
    return;
  }

  node->left()->accept(this, lvl);
  if (is_double(node->type()) && is_int(node->left()->type())) {
    _pf.I2D();
  }
  
  node->right()->accept(this, lvl);
  if (is_double(node->type()) && is_int(node->right()->type())) {
    _pf.I2D();
  }

  if(is_int(node->type()))
    _pf.ADD();
  else if(is_double(node->type()))
    _pf.DADD();
}

void zu::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}

void zu::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  node->left()->accept(this, lvl);
  if (is_double(node->type()) && is_int(node->left()->type())) {
    _pf.I2D();
  }
  
  node->right()->accept(this, lvl);
  if (is_double(node->type()) && is_int(node->right()->type())) {
    _pf.I2D();
  }
  
  if (is_int(node->type())) {
    _pf.MUL();    
  } else if (is_double(node->type())) {
    _pf.DMUL();
  }
}

void zu::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  node->left()->accept(this, lvl);
  if (is_double(node->type()) && is_int(node->left()->type())) {
    _pf.DIV();
  }
  
  node->right()->accept(this, lvl);
  if (is_double(node->type()) && is_int(node->right()->type())) {
    _pf.I2D();
  }
  
  if (is_int(node->type())) {
    _pf.ADD();    
  } else if (is_double(node->type())) {
    _pf.DDIV();
  }
}

void zu::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void zu::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void zu::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}

void zu::postfix_writer::do_or_node(zu::or_node * const node, int lvl) {
  //FIXME

  int lbl1 = ++_lbl;
  int lbl_end = ++_lbl;
  
  node->left()->accept(this, lvl + 1);
  _pf.JNZ(mklbl(lbl1));
  node->right()->accept(this, lvl + 1);
  _pf.JNZ(mklbl(lbl1));
  _pf.INT(0);
  _pf.JMP(mklbl(lbl_end));
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1));
  _pf.INT(1);
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl_end));
}

void zu::postfix_writer::do_and_node(zu::and_node * const node, int lvl) {
  //FIXME

  int lbl0 = ++_lbl;
  int lbl_end = ++_lbl;
  
  node->left()->accept(this, lvl + 1);
  _pf.JZ(mklbl(lbl0));
  node->right()->accept(this, lvl + 1);
  _pf.JZ(mklbl(lbl0));
  _pf.INT(1);
  _pf.JMP(mklbl(lbl_end));
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl0));
  _pf.INT(0);
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl_end));
}


void zu::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void zu::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void zu::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void zu::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->lvalue()->accept(this, lvl);
  
  if(is_double(node->type()))
    _pf.DLOAD();
  else
    _pf.LOAD(); //FIXME: depends on type size
}

//---------------------------------------------------------------------------

//void zu::postfix_writer::do_lvalue_node(zu::lvalue_node * const node, int lvl) {
 /* CHECK_TYPES(_compiler, _symtab, node);
  // simplified generation: all variables are global
  _pf.ADDR(node->value()); */
//}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_assignment_node(zu::assignment_node * const node, int lvl) {
  /*CHECK_TYPES(_compiler, _symtab, node);

  // DAVID: horrible hack!
  // (this is caused by Zu not having explicit variable declarations)
  const std::string &id = node->lvalue()->value();
  std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
  if (symbol->value() == -1) {
    _pf.DATA(); // variables are all global and live in DATA
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(id); // name variable location
    _pf.CONST(0); // initialize it to 0 (zero)
    _pf.TEXT(); // return to the TEXT segment
    symbol->value(0);
  }*/

  node->rvalue()->accept(this, lvl);
  _pf.DUP();
  node->lvalue()->accept(this, lvl);
  _pf.STORE();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); 
  _pf.TRASH(4);
}

void zu::postfix_writer::do_break_node(zu::break_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);

  _pf.JMP(mklbl(_end));
}

void zu::postfix_writer::do_return_node(zu::return_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);

  _pf.JMP(mklbl(_current_function_end));
}

void zu::postfix_writer::do_continue_node(zu::continue_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);

  _pf.JMP(mklbl(_incr));
}

void zu::postfix_writer::do_printcomlinha_node(zu::printcomlinha_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl);

  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi"); //PRINT INTEGER VALUE
    _pf.TRASH(4); // DELETE VALUE
    _pf.EXTERN("printi");
  }

  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints"); //PRINT STRING VALUE
    _pf.TRASH(4); // DELETE VALUE
    _pf.EXTERN("prtins");
  } 

  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd"); //PRINT DOUBLE VALUE
    _pf.TRASH(8); // DELETE VALUE
    _pf.EXTERN("printd");
  } 

  else {
    std::cerr << "ERROR: Trying to print invalid type." << std::endl;
    exit(1);
  }
  
  _pf.CALL("println");
  _pf.EXTERN("println");
  
}

void zu::postfix_writer::do_printsemlinha_node(zu::printsemlinha_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl);

  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi"); //PRINT INTEGER
    _pf.TRASH(4); // DELETE VALUE
    _pf.EXTERN("printi");
  }

  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints"); //PRINT STRING
    _pf.TRASH(4); //DELETE VALUE
    _pf.EXTERN("prtins");
  } 

  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd"); //PRINT DOUBLE
    _pf.TRASH(8); //DELETE VALUE
    _pf.EXTERN("printd");
  } 

  else {
    std::cerr << "ERROR: Trying to print invalid type." << std::endl;
    exit(1);
  }
}

void zu::postfix_writer::do_index_node(zu::index_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  node->expression()->accept(this, lvl);
  _pf.INT(node->shift()); 
  _pf.INT(8);
  _pf.MUL();
  _pf.ADD();
  _pf.DLOAD();
}

void zu::postfix_writer::do_index_expression_node(zu::index_expression_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  
  node->expression()->accept(this, lvl);
  node->shift()->accept(this, lvl);  
  _pf.INT(8);                         
  _pf.MUL();
  _pf.ADD();
  _pf.DLOAD();
}



void zu::postfix_writer::do_malloc_node(zu::malloc_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  
  node->argument()->accept(this, lvl); // IDENTIFY SPACE TO ALLOC  
  _pf.INT(8);                    
  _pf.MUL();  
  _pf.ALLOC();
  _pf.SP();                
}


//---------------------------------------------------------------------------

void zu::postfix_writer::do_read_node(zu::read_node * const node, int lvl) {

  CHECK_TYPES(_compiler, _symtab, node);
  
  if (is_int(node->type()) || node->type()->name() == basic_type::TYPE_UNSPEC) {
    _pf.CALL("readi");
    _pf.EXTERN("readi");
    _pf.PUSH();
  } else {
    _pf.CALL("readd");
    _pf.EXTERN("readd");
    _pf.DPUSH();
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_for_node(zu::for_node * const node, int lvl) {

  CHECK_TYPES(_compiler, _symtab, node);
 
  int cond_lbl = ++_lbl;
  int incr_lbl = ++ _lbl;
  _incr = incr_lbl;
  int end_lbl = ++_lbl;
  _end = end_lbl;
  

  //INIT
  if(node->init() != nullptr){
    node->init()->accept(this, lvl);
  }

  //CONDITION
  _pf.LABEL(mklbl(cond_lbl));
  if(node->condition() != nullptr){ 
    node->condition()->accept(this,lvl);
    _pf.JZ(mklbl(end_lbl));
  }
  
  //BLOCO DO FOR
  node->block()->accept(this,lvl + 2);

  //MAKE LABEL INCREMENT 
  _pf.LABEL(mklbl(incr_lbl)); 

  //INCR
  if(node->incr() != nullptr){
    node->incr()->accept(this,lvl);
    _pf.TRASH(node->init()->size()*4);
  }

  //JUMP TO LABEL
  _pf.JMP(mklbl(cond_lbl));
 
  _pf.LABEL(mklbl(end_lbl));
}

void zu::postfix_writer::do_bloco_node(zu::bloco_node * const node, int lvl) {

  CHECK_TYPES(_compiler, _symtab, node);
  _symtab.push();
  if (node->declarations())
    node->declarations()->accept(this, lvl);
  if (node->statements())
    node->statements()->accept(this, lvl);
  _symtab.pop();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_if_node(zu::if_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_if_else_node(zu::if_else_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//-------------------------------------------------------------------------------

void zu::postfix_writer::do_funcdeclar_node(zu::funcdeclar_node * const node, int lvl){
  CHECK_TYPES(_compiler, _symtab, node);

  const std::string id = node->name();

  if(id == "argc" || id == "argv")
    _pf.EXTERN(id);
}

void zu::postfix_writer::do_func_call_node(zu::func_call_node * const node, int lvl){
  CHECK_TYPES(_compiler, _symtab, node);

  std::string id = fix_main_zu(node->nome());
  std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
  
 //PUT ARGUMENTS IN STACK BY REVERSE ORDER
  int args_size = 0;
  if (node->args() != nullptr) {
    for (int i = node->args()->size() - 1; i >= 0; i--) {
      node->args()->node(i)->accept(this, lvl);
      args_size += ((cdk::expression_node *) node->args()->node(i))->type()->size();
    }
  }
  
  //CALL FUNCTION
  _pf.CALL(id);
  
  //CLEAN STACK
  _pf.TRASH(args_size);
  
  //PUT RETURN VALUE IN STACK
  if (is_int(symbol->type()) || is_pointer(symbol->type()) || is_string(symbol->type())) {
    _pf.PUSH();
  } 
  else if (is_double(symbol->type())) {
    _pf.DPUSH();
  }
  
  _called_functions.push_back(new std::string(id));
}
    
void zu::postfix_writer::do_variable_node(zu::variable_node * const node, int lvl){

  CHECK_TYPES(_compiler, _symtab, node);
  std::string id = node->name();
  std::shared_ptr<zu::symbol> symbol = _symtab.find_local(id);
  bool initial = false;
  if(node->initial_value() != nullptr)
    initial = true;
  
  //LOCAL SCOPE
  if(_current_function != nullptr){ 
    
    if(node->publ() || node->import())
      throw "Local variables cannot be global or extern";

    //FUNCTION ARGUMENTS
    if(_current_offset >= 8){
      
      symbol->offset(_current_offset); //SET VARIABLE OFFSET
      _current_offset += node->type()->size();
    }
    
    else if(_current_offset <= 0){ //LOCAL VARIABLE
      _current_offset -= node->type()->size();
      symbol->offset(_current_offset);
      
      if(initial){
        node->initial_value()->accept(this, lvl + 2);
        _pf.LOCAL(symbol->offset());
       
        if(node->type()->name() == basic_type::TYPE_INT ||
           node->type()->name() == basic_type::TYPE_STRING ||
           node->type()->name() == basic_type::TYPE_POINTER)
          _pf.STORE();
        
        else if(node->type()->name() == basic_type::TYPE_DOUBLE)
          _pf.DSTORE();
      }
    }

    else{
      throw "ERROR: Variable declaration in function";
    }
  }

  //GLOBAL SCOPE
  else{
    if(node->import()){
      _pf.EXTERN(id);
      return;
    }

    if(initial)
      _pf.DATA();
    else
      _pf.BSS();

    _pf.ALIGN();
    
    if(node->publ())
      _pf.GLOBAL(id, _pf.OBJ());

    if(initial){
      _current_id = &id;
      node->initial_value()->accept(this, lvl);
    }
    else{
      _pf.LABEL(id);
      _pf.BYTE(node->type()->size());
    }
  }
}

void zu::postfix_writer::do_func_node(zu::func_node * const node, int lvl) {
 
  CHECK_TYPES(_compiler, _symtab, node);

  _current_function_end = ++ _lbl;

  _pf.TEXT();
  _pf.ALIGN();
  std::string id = fix_main_zu(node->identifier());

  if(node->is_publ())
    _pf.GLOBAL(id, _pf.FUNC());

  _pf.LABEL(id);

  //VISITOR FOR SIZE
  zu::size_zu *visitor = new zu::size_zu(_compiler); 
  node->accept(visitor, 0);
  int size = visitor->size(); 
  delete visitor;

  //RETURN VARIABLE SPACE
  int return_size = 0;
  if(node->return_type() != nullptr){
    if(node->return_type()->name() == basic_type::TYPE_INT ||
       node->return_type()->name() == basic_type::TYPE_STRING ||
       node->return_type()->name() == basic_type::TYPE_POINTER)
      return_size = 4;
    else if(node->return_type()->name() == basic_type::TYPE_DOUBLE)
      return_size = 8;
  }

  _pf.ENTER(size+return_size);


  _current_function = _symtab.find(node->identifier());

  //DEFAULT RETURN VALUE
  if(node->default_return() != nullptr){
    
    node->default_return()->accept(this, lvl + 2);
    
    if(return_size == 4)
      _pf.LOCA(-4); 
    else if(return_size == 8){
      if(node->default_return()->type()->name() == basic_type::TYPE_INT)
        _pf.I2D();
        _pf.LOCAL(-8);
        _pf.DSTORE();
    }
  }
  else{ 

  //IF DEFAULT RETURN IS NOT DEFINED THEN FUNCTION RETURN 0
    if(node->return_type() != nullptr){
      _pf.INT(0);
      _pf.LOCA(-4);
    }
  }

  //ENTER LOCAL CONTEXT
  _symtab.push();

  if(node->arguments() != nullptr){
    _current_offset = 8;  //Offset for function arguments
    node->arguments()->accept(this, lvl + 2);
  }

  _current_offset = 0;  //Local variables offset

  _current_offset -= return_size;


  //BODY OF FUNCTION
  node->block()->accept(this, lvl);

  _pf.ALIGN();
  _pf.LABEL(mklbl(_current_function_end));//generate label for body


  // put return value in eax
  if( return_size == 4){
    _pf.LOCV(-4); //LOCAL(-4) + LOAD()
    _pf.POP(); //REMOVE RETURN VALUE FROM STACK AND PUTS IT IN EAX
  } else if( return_size == 8){
    //SAME PROCEDURE FOR DOUBLE
    _pf.LOCAL(-8);
    _pf.DLOAD();
    _pf.DPOP();
  }

  // RETURN
  _pf.LEAVE();
  _pf.RET();

  //EXIT LOCAL CONTEXT
  _symtab.pop();
  _current_function = nullptr; 
}

void zu::postfix_writer::do_identifier_node(zu::identifier_node * const node, int lvl){
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  
  std::shared_ptr<zu::symbol> symbol = _symtab.find(fix_main_zu(node->identifier()));

  if(_current_function != nullptr){

    if(!symbol->is_var() && _current_function->name() == symbol->name()){
      if(_current_function->type()->name() == basic_type::TYPE_DOUBLE)
        _pf.LOCAL(-8); 
      else
        _pf.LOCAL(-4);
    }

    else if(symbol->offset() == 0)
      _pf.ADDR(fix_main_zu(node->identifier()));

    else if(symbol->offset() != 0 && symbol->is_var())
      _pf.LOCAL(symbol->offset());      
  }

  else
    _pf.ADDR(fix_main_zu(node->identifier()));
}

void zu::postfix_writer::do_identity_node(zu::identity_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  
  node->argument()->accept(this, lvl);
}

void zu::postfix_writer::do_symmetry_node(zu::symmetry_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);

  node->argument()->accept(this, lvl);
  if(node->argument()->type()->name() == basic_type::TYPE_INT)
    _pf.NEG();
  else
    _pf.DNEG();
}

void zu::postfix_writer::do_address_node(zu::address_node * const node, int lvl) {
  //FIXME

  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl);
}