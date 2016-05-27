// $Id: symbol.h,v 1.5 2016/05/20 00:44:17 ist178042 Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_SYMBOL_H__
#define __ZU_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace zu {

    class symbol {
      basic_type *_type;
      std::string _name;
      long _value; // hack!
      bool _is_defined;
      bool _is_var;
      std::vector<basic_type*> _args;
      int _offset;

    public:
      inline symbol(basic_type *type, const std::string &name, bool defined = false) :
          _type(type), _name(name), _is_defined(defined), _is_var(true), _offset(0) {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline long value(long v) {
        return _value = v;
      }
       inline bool is_defined() const {
        return _is_defined; 
      }
      
      inline bool is_defined(bool value) {
        return _is_defined = value; 
      }
      
      inline std::vector<basic_type*> function_args(std::vector<basic_type*> args) {
        return _args = args;  
      }
      inline std::vector<basic_type*> function_args() const {
        return _args; 
      }

      inline int offset(int offset) {
        return _offset = offset;  
      }

      inline int offset() const {
        return _offset; 
      }
      
      inline bool is_var() const {
        return _is_var; 
      }
      
      inline bool is_var(bool value) {
        return _is_var = value; 
      }
    };

} // zu

#endif
