#include <cstdio>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/functor/meta/belong_to.hpp>

struct foo {};
struct bar {};
struct chu {};

int main()
{
  using nt2::meta::set;
  using nt2::meta::belong_to;

  printf("Does foo belong in {foo,bar,chu} : %d\n", belong_to<foo, set<foo,bar,chu> >::value );
  printf("Does foo belong in {foo} : %d\n"        , belong_to<foo, set<foo> >::value );
  printf("Does foo belong in foo : %d\n"          , belong_to<foo, foo>::value );
}
