#include <iostream>
#include <vector>

//#include <nt2/sdk/meta/strip.hpp>

using namespace std;

namespace nt2 { namespace tag
{
  struct cpu_  {};
} }

// new files
#include <nt2/sdk/functor/functor.hpp>

// test
#include <nt2/sdk/functor/details/tags.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/functor/operators.hpp>

NT2_REGISTER_HIERARCHY(vector_)

namespace nt2 { namespace meta
{
  template<class T, class A>
  struct hierarchy_of< std::vector<T,A> >
  {
    typedef vector_<typename hierarchy_of<T>::type > type;
  };
} }

int main()
{
  std::vector<float> k(1337);

  cout << nt2::b_and(-1.0,0x7FFFFFFFFFFFFFFFULL) << "\n";
}
