#pragma once

#include "../include/veg/operators.hpp"
#include "../include/veg/chars.hpp"
#include "../include/veg/context.hpp"

namespace runpac { namespace veg {


typedef set<' ','\n','\r','\t'> space;
typedef plus<space> spaces;
typedef star<space> ws;


template<typename T>
struct tok : public seq<T, ws> {};

template<char C>
struct ch_tok : public seq<ch<C>, ws> {};


typedef ch<'t','r','u','e'>     json_true;
typedef ch<'f','a','l','s','e'> json_false;
typedef ch<'n','u','l','l'>     json_null;


typedef
seq
< ch<'\\'>
, set<'"', '/', '\\', 'b', 'f', 'n', 'r', 't', 'u'>
>
esc_ch;


typedef
seq
< ch<'"'>
, star
  < alter
    < range<'a','z','A','Z','0','9'> // easy
    , ch<' '>
    , esc_ch
    >
  >
, ch<'"'>
>
json_string;


typedef
plus
< range<'0','9'> // easy
>
json_number;


struct json_object;
struct json_array;

struct json_value : public
tok
< alter
  < json_string
  , json_number
  , json_object
  , json_array
  , json_true
  , json_false
  , json_null
  >
> {};


struct json_kv_pair : public
seq
< tok<json_string>
, ch_tok<':'>
, json_value
> {};

struct json_object : public
seq
< ch_tok<'{'>
, opt
  < seq
    < json_kv_pair
    , star
      < seq
        < ch_tok<','>
        , json_kv_pair
        >
      >
    >
  >
, ch<'}'>
> {};


struct json_array : public
seq
< ch_tok<'['>
, opt
  < seq
    < json_value
    , star
      < seq
        < ch_tok<','>
        , json_value
        >
      >
    >
  >
, ch<']'>
> {};

} } // ns

