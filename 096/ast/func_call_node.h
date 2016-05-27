#ifndef __ZU_FUNCTIONCALL_NODE_H__
#define __ZU_FUNCTIONCALL_NODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/expression_node.h>


namespace zu {

  /**
   * Class for describing function call nodes.
   */
  class func_call_node: public cdk::expression_node {
    std::string _nome;
    cdk::sequence_node *_args;

  public:
    inline func_call_node(int lineno, std::string *nome, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _nome(*nome), _args(args) {
    }

  public:
    inline std::string nome() {
      return _nome;
    }
    inline cdk::sequence_node *args() {
      return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_call_node(this, level);
    }

  };

} // zu

#endif