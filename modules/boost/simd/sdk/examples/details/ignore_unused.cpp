#include <nt2/sdk/details/ignore_unused.hpp>

template<class A0,class A1>
A0 return_first(A0 const& a0, A1 const& a1)
{
  nt2::ignore_unused(a1);
  return a0;
}

int main()
{
  int k = return_first(1,"k");
  nt2::ignore_unused(k);
}
