#include <iostream>
#include "targets/size_zu.h"
#include "ast/all.h"

	void zu::size_zu::do_sequence_node(cdk::sequence_node * const node, int lvl){
		for(size_t i = 0; i < node->size(); i++)
			node->node(i)->accept(this, lvl);
	}

    void zu::size_zu::do_bloco_node(zu::bloco_node * const node, int lvl){
        if(node->declarations() != nullptr)
            node->declarations()->accept(this, lvl);
        if(node->statements() != nullptr)
            node->statements()->accept(this, lvl);
    }

    void zu::size_zu::do_for_node(zu::for_node * const node, int lvl){
        if(node->init() != nullptr)
    	   node->init()->accept(this, lvl);
        node->block()->accept(this, lvl);
    }
    void zu::size_zu::do_if_node(zu::if_node * const node, int lvl){
    	node->block()->accept(this, lvl);
    }
    
    void zu::size_zu::do_if_else_node(zu::if_else_node * const node, int lvl){
    	node->thenblock()->accept(this, lvl);
    	if(node->elseblock() != nullptr)
    		node->elseblock()->accept(this, lvl);
    }

    void zu::size_zu::do_func_node(zu::func_node * const node, int lvl){
        node->block()->accept(this, lvl);
    }

    void zu::size_zu::do_variable_node(zu::variable_node * const node, int lvl){
    	_size += (node->type()->name() == basic_type::TYPE_DOUBLE) ? 8 : 4;
    }
