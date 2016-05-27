#ifndef __ZU_VARIABLEDECLARATIONNODE_H__
#define __ZU_VARIABLEDECLARATIONNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>
#include <cdk/ast/identifier_node.h>


namespace zu {

  /**
   * Class for describing variable nodes.
   */
  class variable_node: public cdk::basic_node {
    basic_type *_type;
    std::string _name;
    cdk::expression_node *_inicial_value;
    bool _publ,_import;
    

  public:
    inline variable_node(
      int lineno,
      basic_type *type,
      std::string *name, 
      cdk::expression_node *inicial_value = nullptr, 
      bool publ = false,
      bool import = false ) :
          cdk::basic_node(lineno), 
          _type(type),
          _name(*name), 
          _inicial_value(inicial_value),
          _publ(publ),
          _import(import){}
         

  public:
    inline bool publ() {
      return _publ;
    }
    inline bool import() {
      return _import;
    }
    inline basic_type *type() {
      return _type;
    }
    inline std::string name() {
      return _name;
    }
    inline cdk::expression_node *initial_value() {
      return _inicial_value;
    }
    

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu
#endif