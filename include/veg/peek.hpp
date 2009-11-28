#pragma once

namespace runpac { namespace veg {


template<typename T>
struct peek
{
    template<typename Context>
    static bool match(Context& c)
    {
        auto i = c.pos();
        if (T::match(c)) {
            c.pos(i);
            return true;
        }
        return false;
    }
};



} } //ns
