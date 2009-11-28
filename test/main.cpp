

#include "../include/veg/operators.hpp"
#include "../include/veg/chars.hpp"
#include "../include/veg/context.hpp"

#include "test.hpp"
#include "json.hpp"


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


    return 0;
}
