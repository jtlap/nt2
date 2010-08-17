#include <cstdio>
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/any.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;
using namespace boost::mpl;

int main()
{
  typedef vector<int,bool,float> seq_t;

  typedef nt2::meta::any<is_same<_,bool>,seq_t> any_seq;
  typedef nt2::meta::any<is_same<_,bool>,int,bool,float> any_types;

  printf("is any type bool in vector<int,bool,float> : %d\n", any_seq::value);
  printf("is any type bool in (int,bool,float) : %d\n", any_types::value);
}
