#pragma once

#include <iostream>
#include <string>

namespace runpac { namespace veg {


template<typename Exp>
bool test(const std::string& s, bool should_pass = true)
{

    context<std::string::const_iterator> c(s.begin(), s.end());

    bool b = Exp::match(c);

    std::cout << (b == should_pass ? " PASS " : "-FAIL ") << s << std::endl;

    return b;
}



} } //ns
