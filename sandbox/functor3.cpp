#include <iostream>
#include <vector>

using namespace std;

namespace nt2 { namespace tag
{
  struct cpu_  {};
} }

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
  char c = 4;
  int i = 8;
  cout << (c << i) << "\n";
  cout << nt2::logical_not(2) << "\n";
}
