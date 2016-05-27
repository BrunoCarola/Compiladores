// $Id: malloc_node.h,v 1.2 2016/03/17 17:58:55 ist177974 Exp $ -*- c++ -*-
#ifndef __ZU_MALLOCNODE_H__
#define __ZU_MALLOCNODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing malloc nodes.
   */
  class malloc_node: public cdk::expression_node {
    cdk::expression_node *_argument;

  public:
    inline malloc_node(int lineno, cdk::expression_node *argument) :
        cdk::expression_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_malloc_node(this, level);
    }

  };

} // zu

#endif