#ifndef __ZU_SIZE_ZU_H__
#define __ZU_SIZE_ZU_H__

#include <string>
#include <iostream>
#include <cdk/compiler.h>
#include "targets/basic_ast_visitor.h"


namespace zu {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class size_zu: public basic_ast_visitor {

  int _size;

  public:
    size_zu(std::shared_ptr<cdk::compiler> compiler) : basic_ast_visitor(compiler), _size(0) {
    }

  public:
    ~size_zu() {
      os().flush();
    }

  public:
    int size() { return _size;}

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);
    void do_index_node(zu::index_node * const node, int lvl){}
    void do_index_expression_node(zu::index_expression_node * const node, int lvl){} 

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl){}
    void do_double_node(cdk::double_node * const node, int lvl){}
    void do_string_node(cdk::string_node * const node, int lvl){}

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl){}
    void do_identity_node(zu::identity_node * const node, int lvl){}
    void do_symmetry_node(zu::symmetry_node * const node, int lvl){}

  public:
    void do_add_node(cdk::add_node * const node, int lvl){}
    void do_sub_node(cdk::sub_node * const node, int lvl){}
    void do_mul_node(cdk::mul_node * const node, int lvl){}
    void do_div_node(cdk::div_node * const node, int lvl){}
    void do_mod_node(cdk::mod_node * const node, int lvl){}
    void do_lt_node(cdk::lt_node * const node, int lvl){}
    void do_le_node(cdk::le_node * const node, int lvl){}
    void do_ge_node(cdk::ge_node * const node, int lvl){}
    void do_gt_node(cdk::gt_node * const node, int lvl){}
    void do_ne_node(cdk::ne_node * const node, int lvl){}
    void do_eq_node(cdk::eq_node * const node, int lvl){}
    void do_and_node(zu::and_node * const node, int lvl){}
    void do_or_node(zu::or_node * const node, int lvl){}
  public:
    void do_identifier_node(zu::identifier_node * const node, int lvl){}
    void do_rvalue_node(zu::rvalue_node * const node, int lvl){}

  public:
    void do_evaluation_node(zu::evaluation_node * const node, int lvl){}
    void do_printsemlinha_node(zu::printsemlinha_node * const node, int lvl){}
    void do_printcomlinha_node(zu::printcomlinha_node * const node, int lvl){}
    void do_read_node(zu::read_node * const node, int lvl){}
    void do_assignment_node(zu::assignment_node * const node, int lvl){}

    void do_address_node(zu::address_node * const node, int lvl){}
    void do_malloc_node(zu::malloc_node * const node, int lvl){}
    void do_continue_node(zu::continue_node * const node, int lvl){}
    void do_break_node(zu::break_node * const node, int lvl){}
    void do_return_node(zu::return_node * const node, int lvl){}

  public:
    void do_for_node(zu::for_node * const node, int lvl);
    void do_if_node(zu::if_node * const node, int lvl);
    void do_if_else_node(zu::if_else_node * const node, int lvl);

  public:
    void do_funcdeclar_node(zu::funcdeclar_node * const node, int lvl){}
    void do_variable_node(zu::variable_node * const node, int lvl);
    void do_bloco_node(zu::bloco_node * const node, int lvl);
    void do_func_node(zu::func_node * const node, int lvl);
    void do_func_call_node(zu::func_call_node * const node, int lvl){}
  };

} // zu

#endif