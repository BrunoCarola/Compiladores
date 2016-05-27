#ifndef __ZU_FUNCNDECLARNODE_H__
#define __ZU_FUNCDECLARNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>
#include <cdk/ast/identifier_node.h>


namespace zu {

  /**
   * Class for describing funcdeclar nodes.
   */
  class funcdeclar_node: public cdk::basic_node {
    std::string _name;
    cdk::sequence_node *_arguments;
    basic_type *_return_type;
    bool _public;
    bool _extern;

  public:
    inline funcdeclar_node(
      int lineno, std::string *name, 
      cdk::sequence_node *arguments, 
      basic_type *return_type,
      bool is_public=false,
      bool is_extern = false):
          cdk::basic_node(lineno), 
          _name(*name), _arguments(arguments), 
          _return_type(return_type),
          _public(is_public),
          _extern(is_extern) {}

  public:
    inline std::string name() {
      return _name;
    }
    inline cdk::sequence_node *arguments() {
      return _arguments;
    }
    inline basic_type *return_type() {
      return _return_type;
    }

    inline bool is_public(){return _public;}
    
    inline bool is_extern() { return _extern; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_funcdeclar_node(this, level);
    }

  };

} // zu

#endif