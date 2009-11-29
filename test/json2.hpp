#pragma once

#include <vector>
#include <ctime>
#include <boost/variant.hpp>
#include <boost/unordered_map.hpp>
#include <boost/variant/static_visitor.hpp>

#include "../include/veg/operators.hpp"
#include "../include/veg/chars.hpp"


namespace runpac { namespace veg { namespace jstest {




typedef boost::make_recursive_variant
<
     int, double, bool, const char*, std::string, std::time_t // time_t ?
    ,boost::unordered_map<std::string, boost::recursive_variant_> // object
    ,std::vector<boost::recursive_variant_> // array

>::type xjson_type;

typedef boost::unordered_map<std::string, xjson_type> xjson_object;
typedef std::vector<xjson_type> xjson_array;




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
  < store<json_string>
  , store<json_number>
  , store<json_object>
  , store<json_array>
  , store<json_true>
  , store<json_false>
  , store<json_null>
  >
> {};


struct json_kv_pair : public
seq
< tok<store<json_string> >
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
> {
  //////////static int type_id = 4;

};


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

} } } // ns

