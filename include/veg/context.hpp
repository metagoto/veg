#pragma once

//tmp

namespace runpac { namespace veg {


template<typename Iterator>
struct context
{

    typedef Iterator iterator_type;
    typedef typename Iterator::value_type value_type;

    context(iterator_type beg, iterator_type end)
        : beg(beg)
        , end(end)
        , it(beg)
    {
    }


    iterator_type pos()
    {
        return it;
    }

    void pos(iterator_type i)
    {
        it = i;
    }

    value_type operator*()
    {
        return *it;
    }

    void operator++()
    {
        ++it;
    }

    value_type operator++(int i)
    {
        return it++;
    }

    bool eoi()
    {
        return it == end;
    }



    iterator_type beg;
    iterator_type end;
    iterator_type it;

};



} } //ns
