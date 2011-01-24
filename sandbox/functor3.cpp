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


NT2_REGISTER_DISPATCH(Tag,tag::cpu_,(Tag)(A0),(vector_<A0>));
NT2_REGISTER_DISPATCH(Tag,tag::cpu_,(Tag)(A0)(A1),(vector_<A0>)(vector_<A1>));

namespace nt2 { namespace ext
{
  template<class Tag, class H, class Dummy>
  struct  call<Tag(tag::vector_(H)), tag::cpu_, Dummy>
        : callable
  {
    typedef std::size_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0.size();
    }
  };

  template<class Tag, class H0, class H1, class Dummy>
  struct  call<Tag(tag::vector_(H0),tag::vector_(H1)), tag::cpu_, Dummy>
        : callable
  {
    typedef std::size_t result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return a0.size()*a1.size();
    }
  };

  template<class H, class Dummy>
  struct  call<tag::complement_(tag::vector_(H)), tag::cpu_, Dummy>
        : callable
  {
    typedef std::size_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return 100*a0.size();
    }
  };
} }

int main()
{
  std::vector<float> x(159);
  char c = 4;
  int i = 8;
  cout << nt2::logical_not(2) << "\n";
  cout << nt2::logical_not(x) << "\n";
  cout << nt2::complement(x) << "\n";
  cout << nt2::then(19,.321f) << "\n";
  //cout << nt2::complement("lol") << "\n";
}
