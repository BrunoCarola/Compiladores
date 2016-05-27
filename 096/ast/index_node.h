#ifndef __Z_INDEX_H__
#define __Z_INDEX_H__

#include <cdk/ast/simple_value_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding index lvalues.
   */
  class index_node: public zu::lvalue_node {
  
  private:
    int _shift;
    cdk::expression_node *_expression;

  public:
    inline index_node(int lineno, cdk::expression_node *node, int shift) :
        zu::lvalue_node(lineno), _shift(shift), _expression(node) {
    }

    inline int shift() { return _shift; }
    inline cdk::expression_node * expression() { return _expression; }
    
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // zu

#endif
