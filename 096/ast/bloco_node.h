#ifndef __ZU_BLOCONODE_H__
#define __ZU_BLOCONODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/basic_node.h>

namespace zu {

  /**
   * Class for describing bloco nodes.
   */
  class bloco_node: public cdk::basic_node {
    cdk::sequence_node *_declarations;
    cdk::sequence_node *_statements;

  public:
    inline bloco_node(int lineno, cdk::sequence_node *declarations = nullptr, cdk::sequence_node *statements = nullptr) :
        cdk::basic_node(lineno), _declarations(declarations), _statements(statements) {
    }

  public:
    inline cdk::sequence_node *declarations() {
      return _declarations;
    }
    inline cdk::sequence_node *statements() {
      return _statements;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_bloco_node(this, level);
    }

  };

} // zu

#endif