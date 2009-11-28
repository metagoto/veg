#pragma once

#include "alter.hpp"

namespace runpac { namespace veg {


template<char... Args>
struct range;


template<char L, char R>
struct range<L, R>
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi() && *c >= L && *c <= R) {
            ++c;
            return true;
        }
        return false;
    }
};


template<char L, char R, char... Args>
struct range<L, R, Args...>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return alter<range<L,R>, range<Args...>>::match(c);
    }
};


} } //ns
