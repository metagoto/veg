
#include "../include/veg/operators.hpp"
#include "../include/veg/chars.hpp"
#include "../include/veg/context.hpp"
#include "../include/veg/actor.hpp"

#include "../include/veg/store.hpp"
#include "../include/veg/ast.hpp"


#include "test.hpp"
#include "json.hpp"
#include "json2.hpp"


using namespace runpac::veg;


typedef seq< ch<'a'>, ch<'b'> > t0;

typedef seq< alter<ch<'a'>, ch<'b'> > > t1;

typedef alter< seq<ch<'a'>, ch<'b'> >, seq<ch<'b', 'a', 'f'>, ch<'o'>, ch<'f'> > > t2;

typedef seq< star<ch<'a'>> , ch<'c'> > t3;

typedef plus<ch<'a'>> t4;

typedef seq<opt<ch<'b'>>, ch<'c'>> t5;

typedef seq<peek<ch<'a'>>, ch<'a','b'>> t6;

typedef repeat<seq<ch<'a'>, ch<'b', 'c'>>, 2> t7;

typedef seq<ch<'/','*'>, until<ch<'*','/'>>, ch<'*','/','e'>> t8;

typedef seq<ch<'/','*'>, until_past<ch<'*','/'>>, ch<'e'>> t9;

typedef seq<t9, eoi> t10;

typedef seq<ch<'a'>, eoi> t11;

typedef eoi t12;

typedef range<'a','d'> t13;

typedef range<'a','d', 'A','X'> t14;

typedef range<'A','Z', '0','9'> t15;

typedef set<'v', 'e', 'g', '#'> t16;


struct echo_act
{
    typedef std::string::const_iterator it_type;
    void operator()(it_type&& s, it_type&& e)
    {
        std::cout << std::string(s, e) << std::endl;
    }
};

typedef actor<ch<'s','a','l','u','t'>, echo_act> t17;

typedef seq<t17, ch<'x'>> t18;



namespace runpac { namespace veg {

template<>
struct type_to_int<jstest::json_string>
{  static const int num = 1; };

template<>
struct type_to_int<jstest::json_number>
{  static const int num = 2; };

template<>
struct type_to_int<jstest::json_object>
{  static const int num = 3; };

template<>
struct type_to_int<jstest::json_array>
{  static const int num = 4; };

template<>
struct type_to_int<jstest::json_true>
{  static const int num = 5; };
\
template<>
struct type_to_int<jstest::json_false>
{  static const int num = 6; };

template<>
struct type_to_int<jstest::json_null>
{  static const int num = 7; };

} } // ns


struct json_type_converter_visitor : public boost::static_visitor<>
{
    void operator()(const jstest::xjson_object& val) const
    {
        for (jstest::xjson_object::const_iterator i(val.begin()), e(val.end()); i != e; ++i) {
            std::cout << i->first << std::endl;
            boost::apply_visitor( json_type_converter_visitor(), i->second );
        }
    }

    void operator()(const jstest::xjson_array& val) const
    {
        for (jstest::xjson_array::const_iterator i(val.begin()), e(val.end()); i != e; ++i) {
            boost::apply_visitor( json_type_converter_visitor(), *i );
        }
    }

    template<typename T>
    void operator()(const T& val) const
    {
        std::cout << val << std::endl;
    }
};



static jstest::xjson_type describe(ast<std::string>::node_base* n)
{

    switch (n->type())
    {

        case 1 : // string
            return n->str();
        case 2 : // num, true, false, null
        case 5 :
        case 6 :
        case 7 :
            return n->str();
        case 3 :  { // obj
            jstest::xjson_object obj;
            auto i = n->children.begin();
            auto e = n->children.end();
            for ( ; i != e; ++i) {
                std::string key = (*i)->str();
                ++i;
                obj[key] = describe(*i);
            }
            return obj;
        }
        case 4 : { // array
            jstest::xjson_array arr;
            auto i = n->children.begin();
            auto e = n->children.end();
            for ( ; i != e; ++i) {
                arr.push_back(describe(*i));
            }
            return arr;
        }
        case 0 : // should not reach
        default :
            ;
    }
    return jstest::xjson_object();
}


struct json_parser : public ast<std::string>
{

    json_parser(const std::string& s)
    {

        tree_context<std::string::const_iterator, json_parser> c(s.begin(), s.end(), *this);

        bool b = jstest::json_value::match(c);

        if (b) {
            traverse();
            jstest::xjson_type json = describe();
            boost::apply_visitor( json_type_converter_visitor(), json );
        }
    }

    jstest::xjson_type describe()
    {
        return ::describe(*(root->children.begin()));
    }

};



//g++ -std=c++0x -Wall -o prog test/main.cpp -I/Users/runpac/dev/boost_44/include
int main()
{

    test<t0>("ab");
    test<t1>("ab");
    test<t2>("bafof");
    test<t3>("aaaaac");

    test<t4>("a");
    test<t4>("aaa");
    test<t4>("b", false);

    test<t5>("bc");
    test<t5>("c");
    test<t5>("bbc", false);

    test<t6>("ab");
    test<t6>("zab", false);

    test<t7>("abcabc");
    test<t7>("zabcabc", false);
    test<t7>("abcab", false);

    test<t8>("/*gjgh*/e");
    test<t8>("/*gjgh/e", false);

    test<t9>("/*gjgh*/e");
    test<t9>("/*gjgh/e", false);

    test<t10>("/*gjgh*/e");
    test<t10>("/*gjgh*/ez", false);

    test<t11>("sss", false);
    test<t11>("a");

    test<t12>("");
    test<t12>("ds", false);

    test<t13>("a");
    test<t13>("b");
    test<t13>("d");
    test<t13>("e", false);

    test<t14>("A");
    test<t14>("b");
    test<t14>("X");
    test<t14>("Z", false);

    test<t15>("0");
    test<t15>("2");
    test<t15>("Z");
    test<t15>("p", false);

    test<t16>("v");
    test<t16>("e");
    test<t16>("g");
    test<t16>("#");
    test<t16>("x", false);

    test<json_string>("\"df\\\\jk  hk\\nj\\\"lkl\" ");
    test<json_number>("12");
    test<json_object>("{\"key\": \"val\" , \"key2\" : true }");
    test<json_array>("[1, 2 ]");
    test<json_array>("[1,2, \"str\" , { \"key\" :  \"val\" , \"key2\": true }]");

    test<t17>("salut");
    test<t17>("saluz", false);

    test<t18>("salutx");
    test<t18>("salutZ", false);

    json_parser p0("42");
    json_parser p1("\"key\"");
    json_parser p2("[\"blah\", [], true]");
    json_parser p3("[1,2, \"str\" , { \"key\" :  \"val\", \"key2\": [true, null] }, false,[]]");


    return 0;
}
