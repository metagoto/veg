#pragma once

namespace runpac { namespace veg {


template<typename... Args>
struct seq;

template<typename T>
struct seq<T>
{
    template<typename Context>
    static bool match(Context& c)
    {
        return T::match(c);
    }
};

template<typename T, typename ...Args>
struct seq<T, Args...>
{
    typedef seq<Args...> rest;

    template<typename Context>
    static bool match(Context& c)
    {
        auto i = c.pos();
        if (T::match(c) && rest::match(c)) {
            return true;
        }
        c.pos(i);
        return false;
    }
};


} } //ns
