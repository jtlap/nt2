#include <boost/mpl/assert.hpp>
#include <nt2/sdk/meta/is_result_of_supported.hpp>

using nt2::meta::is_result_of_supported;

struct foo { typedef float result_type; };

struct bar
{
  template<class Sig> struct result;
  template<class This,class A,class B>
  struct result<This(A,B)>    { typedef B type; };
};

int main()
{
  BOOST_MPL_ASSERT    (( is_result_of_supported<bar(int,void*)>       ));
  BOOST_MPL_ASSERT    (( is_result_of_supported<foo(int,int,int)>     ));
  BOOST_MPL_ASSERT_NOT(( is_result_of_supported<float(int)>           ));
  BOOST_MPL_ASSERT_NOT(( is_result_of_supported<bar(int,float,char*)> ));
}

