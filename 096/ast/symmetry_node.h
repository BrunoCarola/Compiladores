#ifndef __ZU_SYMMETRYNODE__
#define __ZU_SYMMETRYNODE__

#include <cdk/ast/unary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing the identity operator
   */
  class symmetry_node: public cdk::unary_expression_node {
  public:
    inline symmetry_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_symmetry_node(this, level);
    }

  };

} // zu

#endif