#ifndef __ZU_NODE__LEFTVALUE_H__
#define __ZU_NODE__LEFTVALUE_H__

#include <cdk/ast/expression_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
   
  class lvalue_node: public cdk::expression_node {
    
  public:
    inline lvalue_node(int lineno) :
        expression_node(lineno) {
    }

    virtual void accept(basic_ast_visitor *sp, int level) = 0;

  };

} // zu

#endif
