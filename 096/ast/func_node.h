// $Id: func_node.h,v 1.3 2016/05/18 22:54:54 ist177974 Exp $ -*- c++ -*-
#ifndef __CDK_FUNCNODE_H__
#define __CDK_FUNCNODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>

namespace zu {

  /**
   * Class func describing function nodes.
   */
  class func_node: public cdk::basic_node {
    basic_type *_return_type;
    std::string _identifier;
    cdk::sequence_node *_arguments;
    cdk::expression_node *_default_return;
    bloco_node *_block;
    bool _public;

  public:
    inline func_node(int lineno,
      basic_type *return_type,
      std::string *identifier,
      cdk::sequence_node *arguments, 
      cdk::expression_node *default_return, 
      bloco_node *block, 
      bool publ=false) :
        basic_node(lineno), _return_type(return_type), _identifier(*identifier), _arguments(arguments), 
        _default_return(default_return), _block(block), _public(publ){
    }

  public:

    inline basic_type *return_type() {
      return _return_type;
    }

    inline std::string identifier() {
      return _identifier;
    }
    
    inline cdk::sequence_node *arguments(){
      return _arguments;
    }

    inline cdk::expression_node *default_return(){
      return _default_return;
    }

    inline bloco_node *block() {
      return _block;
    }

    inline bool is_publ(){ 
      return _public;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_node(this, level);
    }

  };

} // zu

#endif
