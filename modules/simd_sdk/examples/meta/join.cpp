#include <cstdio>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/join.hpp>
#include <nt2/sdk/meta/is_set.hpp>
#include <nt2/sdk/meta/has_key.hpp>

int main()
{
  typedef nt2::meta::set<double,float>    reals;
  typedef nt2::meta::set<char,short,int>  ints;
  typedef nt2::meta::join<reals,ints>     joined;

  printf("Is joined a set: %d\n",nt2::meta::is_set<joined>::value);
  printf("Is int    in joined: %d\n",nt2::meta::has_key<joined,int>::value);
  printf("Is void   in joined: %d\n",nt2::meta::has_key<joined,void>::value);
  printf("Is double in joined: %d\n",nt2::meta::has_key<joined,double>::value);
}
