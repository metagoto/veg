#pragma once

namespace runpac { namespace veg {


template<char... Args>
struct ch;


template<char C>
struct ch<C>
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi() && *c == C) {
            ++c;
            return true;
        }
        return false;
    }
};


template<char C, char... Args>
struct ch<C, Args...>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return seq<ch<C>, ch<Args...>>::match(c);
    }

};



} } //ns
