#ifndef __ZU_INDEX_EXPRESSION_NODE_H__
#define __ZU_INDEX_EXPRESSION_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/identifier_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding index expressions.
   */
  class index_expression_node: public zu::lvalue_node {
  
  private:
    cdk::expression_node *_expression;
    cdk::expression_node *_shift;
    
  public:
    inline index_expression_node(int lineno, cdk::expression_node *node, cdk::expression_node *shift) :
        zu::lvalue_node(lineno), _expression(node), _shift(shift){}

    inline cdk::expression_node *shift() {return _shift;}
    inline cdk::expression_node *expression() {return _expression;}

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_expression_node(this, level);
    }

  };

} // ZU

#endif