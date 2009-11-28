#pragma once

namespace runpac { namespace veg {


template<typename T, unsigned int N>
struct repeat
{
    template<typename Context>
    static bool match(Context& c)
    {
        auto i = c.pos();
        for (unsigned int n = 0; n < N; ++n) {
            if (!T::match(c)) {
                c.pos(i);
                return false;
            }
        }
        return true;
    }
};



} } //ns
