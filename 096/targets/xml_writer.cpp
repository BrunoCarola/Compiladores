// $Id: xml_writer.cpp,v 1.24 2016/05/19 21:58:13 ist177974 Exp $ -*- c++ -*-
#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void zu::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  processSimple(node, lvl);
}

void zu::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void zu::xml_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void zu::xml_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void zu::xml_writer::do_or_node(zu::or_node * const node, int lvl) {
  //FIXME
  processBinaryExpression(node, lvl);
}

void zu::xml_writer::do_and_node(zu::and_node * const node, int lvl) {
  //FIXME
  processBinaryExpression(node, lvl);
}

void zu::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

/*void zu::xml_writer::do_lvalue_node(zu::lvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
 // os() << std::string(lvl+2, ' ') << "<left-value>" << node->shift() << "</left-value>" << std::endl; 
  closeTag(node, lvl);
}*/

//---------------------------------------------------------------------------

void zu::xml_writer::do_assignment_node(zu::assignment_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("left-value", lvl + 2);
  node->lvalue()->accept(this, lvl + 4);
  closeTag("lvalue", lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void zu::xml_writer::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

/*void zu::xml_writer::do_print_node(zu::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}*/

void zu::xml_writer::do_break_node(zu::break_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  closeTag(node, lvl);
}

void zu::xml_writer::do_continue_node(zu::continue_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  closeTag(node, lvl);
}

void zu::xml_writer::do_return_node(zu::return_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  closeTag(node, lvl);
}

/*void zu::xml_writer::do_indicapos_node(zu::indicapos_node * const node, int lvl) {
  //FIXME
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}*/

void zu::xml_writer::do_printcomlinha_node(zu::printcomlinha_node * const node, int lvl) {
  //FIXME
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_printsemlinha_node(zu::printsemlinha_node * const node, int lvl) {
  //FIXME
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_index_expression_node(zu::index_expression_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  openTag("expression", lvl + 2);
  node->expression()->accept(this, lvl + 4);
  closeTag("expression", lvl + 2);
  openTag("shift", lvl + 2);
  node->shift()->accept(this, lvl + 4);
  closeTag("shift", lvl + 2);  
  closeTag(node, lvl);
}

void zu::xml_writer::do_index_node(zu::index_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<shift>" << node->shift() << "</shift>" << std::endl;
  openTag("expression", lvl + 2);
  node->expression()->accept(this, lvl + 4);
  closeTag("expression", lvl + 2);
  closeTag(node, lvl);
}


void zu::xml_writer::do_malloc_node(zu::malloc_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  doCanBeNull("argument", node->argument(), lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_funcdeclar_node(zu::funcdeclar_node * const node, int lvl){
  //FIXME
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<name>" << node->name() << "</name>" << std::endl; 
  if (node->arguments() != nullptr) {
      openTag("arguments", lvl + 2);
      node->arguments()->accept(this, lvl + 4);
      closeTag("arguments", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<arguments></arguments>" << std::endl;
  }  
  processFuncReturnType(node->return_type(), lvl + 2);
  closeTag(node, lvl);

}

void zu::xml_writer::do_variable_node(zu::variable_node * const node, int lvl){
  //FIXME
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<name>" << node->name() << "</name>" << std::endl;
 if (node->initial_value() != nullptr) {
      openTag("initial_value", lvl + 2);
      node->initial_value()->accept(this, lvl + 4);
      closeTag("initial_value", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<arguments></arguments>" << std::endl;
  }
  processVarType(node->type(), lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_func_call_node(zu::func_call_node * const node, int lvl){
  //FIXME
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<name>" << node->nome() << "</name>" << std::endl; 
  if (node->args() != nullptr) {
      openTag("arguments", lvl + 2);
      node->args()->accept(this, lvl + 4);
      closeTag("arguments", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<arguments></arguments>" << std::endl;
  }
  closeTag(node, lvl);
}

void zu::xml_writer::do_func_node(zu::func_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  processFuncReturnType(node->return_type(), lvl + 2);

  os() << std::string(lvl + 2, ' ') << "<identifier>" << node->identifier() << "</identifier>" << std::endl; 
  if (node->arguments() != nullptr) {
      openTag("arguments", lvl + 2);
      node->arguments()->accept(this, lvl + 4);
      closeTag("arguments", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<arguments></arguments>" << std::endl;
  }   
  openTag("default_return", lvl + 2);
  node->default_return()->accept(this, lvl + 4);
  closeTag("default_return", lvl + 2);
  if (node->block() != nullptr) {
      openTag("block", lvl + 2);
      node->block()->accept(this, lvl + 4);
      closeTag("block", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<block></block>" << std::endl;
  } 
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_read_node(zu::read_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl); 
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_for_node(zu::for_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  if (node->init() != nullptr) {
      openTag("init", lvl + 2);
      node->init()->accept(this, lvl + 4);
      closeTag("init", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<init></init>" << std::endl;
  } 
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  if (node->incr() != nullptr) {
      openTag("incr", lvl + 2);
      node->incr()->accept(this, lvl + 4);
      closeTag("incr", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<incr></incr>" << std::endl;
  } 
  if (node->block() != nullptr) {
      openTag("block", lvl + 2);
      node->block()->accept(this, lvl + 4);
      closeTag("block", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<block></block>" << std::endl;
  } 
  closeTag(node, lvl);
}

void zu::xml_writer::do_bloco_node(zu::bloco_node * const node, int lvl) {
  //FIXME
  openTag(node, lvl);
  if (node->declarations() != nullptr) {
      openTag("declarations", lvl + 2);
      node->declarations()->accept(this, lvl + 4);
      closeTag("declarations", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<declarations></declarations>" << std::endl;
  } 
  if (node->statements() != nullptr) {
      openTag("statements", lvl + 2);
      node->statements()->accept(this, lvl + 4);
      closeTag("statements", lvl + 2);
  } else {
      os() << std::string(lvl+2, ' ') << "<statements></statements>" << std::endl;
  } 
  closeTag(node, lvl);
}

void zu::xml_writer::do_identifier_node(zu::identifier_node * const node, int lvl){
  //FIXME
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<identifier>" << node->identifier() << "</identifier>" << std::endl; 
  closeTag(node, lvl);
}

void zu::xml_writer::do_identity_node(zu::identity_node * const node, int lvl){
  //FIXME
  processUnaryExpression(node, lvl);
}

void zu::xml_writer::do_symmetry_node(zu::symmetry_node * const node, int lvl){
  //FIXME
  processUnaryExpression(node, lvl);

}

void zu::xml_writer::do_address_node(zu::address_node * const node, int lvl){
  //FIXME
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_if_node(zu::if_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_if_else_node(zu::if_else_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  if (node->elseblock() != nullptr) {
      openTag("else", lvl + 2);
      node->elseblock()->accept(this, lvl + 4);
      closeTag("else", lvl + 2);
  } 
  closeTag(node, lvl);
}
