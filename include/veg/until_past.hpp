#pragma once


namespace runpac { namespace veg {


template<typename T>
struct until_past
{

    template<typename Context>
    static bool match(Context& c)
    {
        auto i = c.pos();
        while (true) {
            if (T::match(c)) {
                return true;
            }
            ++c;
            if (c.eoi()) {
                c.pos(i);
                return false;
            }
        }
        return false;
    }

};



} } //ns
