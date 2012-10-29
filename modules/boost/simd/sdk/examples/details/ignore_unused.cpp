#include <boost/dispatch/details/ignore_unused.hpp>

template<class A0,class A1>
A0 return_first(A0 const& a0, A1 const& a1)
{
  boost::dispatch::ignore_unused(a1);
  return a0;
}

int main()
{
  int k = return_first(1,"k");
  boost::dispatch::ignore_unused(k);
}
