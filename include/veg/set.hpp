#pragma once

#include "ch.hpp"

namespace runpac { namespace veg {


template<char... Args>
struct set;


template<char C>
struct set<C>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return ch<C>::match(c);
    }
};


template<char C, char... Args>
struct set<C, Args...>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return ch<C>::match(c) || set<Args...>::match(c);
    }

};



} } //ns
