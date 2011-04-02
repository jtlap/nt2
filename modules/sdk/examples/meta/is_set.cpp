#include <cstdio>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/is_set.hpp>

int main()
{
  typedef nt2::meta::set<int,float,double**>  s;
  typedef nt2::meta::is_set<s>                is;
  typedef nt2::meta::is_set<long**>           il;

  printf("%d %d\n",is::value,il::value);
}
