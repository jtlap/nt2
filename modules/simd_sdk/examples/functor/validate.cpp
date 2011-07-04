#include <cstdio>
#include <string>
#include <nt2/sdk/functor/operators.hpp>
#include <nt2/sdk/functor/meta/validate.hpp>

int main()
{
  using nt2::meta::validate;
  using nt2::functors::plus_;

  printf( "nt2::plus(int,int)       : %d\n", nt2::meta::result_of<validate<plus_>(int,int)>::type::value );
  printf( "nt2::plus(string,string) : %d\n", nt2::meta::result_of<validate<plus_>(std::string,std::string)>::type::value );
}
