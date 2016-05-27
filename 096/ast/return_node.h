// $Id: return_node.h,v 1.4 2016/04/15 15:43:56 ist178042 Exp $ -*- c++ -*-
#ifndef __ZU_RETURNNODE_H__
#define __ZU_RETURNNODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing return nodes.
   */
  class return_node: public cdk::basic_node {
    cdk::expression_node *_argument;

  public:
    inline return_node(int lineno) :
        cdk::basic_node(lineno) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }

  };

} // zu

#endif