// $Id: postfix_writer.h,v 1.20 2016/05/20 13:52:06 ist177974 Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_PF_WRITER_H__
#define __ZU_SEMANTICS_PF_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace zu {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<zu::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    std::shared_ptr<symbol> _current_function;
    int _current_offset;
    int _current_function_end;
    int _incr, _end;
    std::string *_current_id;
    std::vector<std::string *> _declared_functions;
    std::vector<std::string *> _defined_functions;
    std::vector<std::string *> _called_functions;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<zu::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0) {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }

    inline std::string fix_main_zu(std::string id) {
      if (id == "zu") return std::string("_main");
      if (id == "_main") return "._main";
      return id;
    }

  private:
    //!
    //! CHECK TYPES
    //!
   bool is_int(basic_type *type) {
      return type->name() == basic_type::TYPE_INT;
    }
    
    bool is_double(basic_type *type) {
      return type->name() == basic_type::TYPE_DOUBLE;
    }
    
    bool is_pointer(basic_type *type) {
      return type->name() == basic_type::TYPE_POINTER;
    }
    
    bool is_string(basic_type *type) {
      return type->name() == basic_type::TYPE_STRING;
    }
    
    bool is_void(basic_type *type) {
      return type->name() == basic_type::TYPE_VOID;
    }
    
    bool is_lval(cdk::basic_node * const node) {
      std::string name(node->name());
      return name == "index_node" || name == "lvalue_node"; 
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    void do_or_node(zu::or_node * const node, int lvl);
    void do_and_node(zu::and_node * const node, int lvl);

  public:
    //void do_lvalue_node(zu::lvalue_node * const node, int lvl);
    void do_rvalue_node(zu::rvalue_node * const node, int lvl);

  public:
    void do_evaluation_node(zu::evaluation_node * const node, int lvl);
    void do_break_node(zu::break_node * const node, int lvl);
    void do_continue_node(zu::continue_node * const node, int lvl);
    void do_return_node(zu::return_node * const node, int lvl);
    void do_printcomlinha_node(zu::printcomlinha_node * const node, int lvl);
    void do_printsemlinha_node(zu::printsemlinha_node * const node, int lvl);
    void do_index_node(zu::index_node * const node, int lvl);
    void do_malloc_node(zu::malloc_node * const node, int lvl);
    //void do_indicapos_node(zu::indicapos_node * const node, int lvl);
    void do_index_expression_node(zu::index_expression_node * const node, int lvl);

    void do_read_node(zu::read_node * const node, int lvl);
    void do_assignment_node(zu::assignment_node * const node, int lvl);

  public:
    void do_for_node(zu::for_node * const node, int lvl);
    void do_if_node(zu::if_node * const node, int lvl);
    void do_if_else_node(zu::if_else_node * const node, int lvl);
    void do_bloco_node(zu::bloco_node * const node, int lvl);
    void do_funcdeclar_node(zu::funcdeclar_node * const node, int lvl);
    void do_variable_node(zu::variable_node * const node, int lvl);
    void do_func_node(zu::func_node * const node, int lvl);
    void do_func_call_node(zu::func_call_node * const node, int lvl);
    void do_identifier_node(zu::identifier_node * const node, int lvl);
    void do_identity_node(zu::identity_node * const node, int lvl);
    void do_address_node(zu::address_node * const node, int lvl);
    void do_symmetry_node(zu::symmetry_node * const node, int lvl);

  };

} // zu

#endif
