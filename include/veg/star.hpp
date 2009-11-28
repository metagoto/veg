#pragma once

namespace runpac { namespace veg {


template<typename T>
struct star
{
    template<typename Context>
    static bool match(Context& c)
    {
        if (!c.eoi()) {
            while (T::match(c));
        }
        return true;
    }
};



} } //ns
