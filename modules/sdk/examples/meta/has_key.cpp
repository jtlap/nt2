#include <cstdio>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>

int main()
{
  typedef nt2::meta::set<double,float>    reals;
  typedef nt2::meta::set<char,short,int>  ints;

  printf("Is int    in reals: %d\n",nt2::meta::has_key<reals,int>::value);
  printf("Is int    in ints : %d\n",nt2::meta::has_key<ints ,int>::value);
  printf("Is double in reals: %d\n",nt2::meta::has_key<reals,double>::value);
  printf("Is double in ints : %d\n",nt2::meta::has_key<ints ,double>::value);
}
