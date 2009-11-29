#pragma once

#include <algorithm>
#include <functional>
#include <list>

namespace runpac { namespace veg {


template<typename T>
struct type_to_int
{
    static const int num = 0;
};


template<typename String>
struct ast
{

    typedef String string_type;
    typedef typename String::const_iterator iterator_type;


    struct node_base
    {

        node_base()
            : parent(0)
        {}

        node_base(iterator_type s)
            : parent(0)
            , start(s)
        {
        }


        void add_child(node_base* child)
        {
            children.push_back(child);
            child->parent = this;
        }


        void remove_child(node_base* child)
        {
            auto it = std::find(children.begin(), children.end(), child);
            if (it != children.end()) {
                delete *it;
                children.erase(it);
            }
        }

        virtual ~node_base()
        {
            typename std::list<node_base*>::iterator s = children.begin();
            typename std::list<node_base*>::iterator e = children.end();
            std::for_each(s, e, std::bind1st(std::mem_fun(&node_base::remove_child), this));
        }


        void traverse(int depth = 0) const
        {
            auto i = children.begin();
            auto e = children.end();
            for ( ; i != e; ++i) {

                //debug
                std::cout << depth << "; " << (*i)->str() << " TYPE: " << (*i)->type() << std::endl;

                (*i)->traverse(depth+1);
            }
        }



        string_type str() const
        {
            return string_type(start, end);
        }


        virtual int type()
        {
            return 0;
        }


        iterator_type start;
        iterator_type end;

        node_base* parent;

        std::list<node_base*> children;

    };


    template<typename T>
    struct node : public node_base
    {
        node(iterator_type s)
            : node_base(s)
        {
        }

        virtual int type()
        {
            return type_to_int<T>::num;
        }

    };




    void finalize_node(iterator_type e)
    {
        current->end = e;
        current = current->parent;
    }

    void forget_node()
    {
        node_base* old = current;
        current = current->parent;
        current->remove_child(old);
    }

    template<typename T>
    void create_node(iterator_type s)
    {
        node_base* n = new node<T>(s);
        current->add_child(n);
        current = n;
    }


    ast()
        : root(new node_base())
        , current(root)
    {
    }

    void traverse()
    {
        root->traverse();
    }

    node_base* root;
    node_base* current;

};



} } //ns
