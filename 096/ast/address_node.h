#ifndef __ZU_ADDRESSNODE__
#define __ZU_ADDRESSNODE__

#include <cdk/ast/unary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing the identity operator
   */
  class address_node: public cdk::unary_expression_node {
  public:
    inline address_node(int lineno, cdk::expression_node *pos) :
        cdk::unary_expression_node(lineno, pos) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_address_node(this, level);
    }

  };

} // zu

#endif