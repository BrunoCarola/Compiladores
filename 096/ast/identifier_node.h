#ifndef __IDENTIFIER_NODE_H__
#define __IDENTIFIER_NODE_H__

#include <string>
#include <ast/lvalue_node.h>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding identifier
   * values.
   */
  class identifier_node: public zu::lvalue_node {
  private:
    std::string _identifier;

  public:
    inline identifier_node(int lineno, const char *s) :
        lvalue_node(lineno), _identifier(s) {
    }
    inline identifier_node(int lineno, const std::string &s) :
        lvalue_node(lineno), _identifier(s) {
    }
    inline identifier_node(int lineno, const std::string *s) :
        lvalue_node(lineno), _identifier(*s) {
    }

    inline std::string identifier() {
      return _identifier;
    }
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identifier_node(this, level);
    }

  };

} // zu

#endif