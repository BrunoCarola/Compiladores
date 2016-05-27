// $Id: printsemlinha_node.h,v 1.1 2016/03/17 12:55:06 ist177974 Exp $ -*- c++ -*-
#ifndef __ZU_PRINTSEMLINHANODE_H__
#define __ZU_PRINTSEMLINHANODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing print nodes.
   */
  class printsemlinha_node: public cdk::basic_node {
    cdk::expression_node *_argument;

  public:
    inline printsemlinha_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_printsemlinha_node(this, level);
    }

  };

} // zu

#endif