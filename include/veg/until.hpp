#pragma once

#include "until_past.hpp"
#include "peek.hpp"

namespace runpac { namespace veg {


template<typename T>
struct until : public until_past<peek<T>>
{

};



} } //ns
