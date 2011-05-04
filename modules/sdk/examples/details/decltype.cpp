#include <vector>
#include <iostream>
#include <nt2/sdk/details/decltype.hpp>

int main()
{
  NT2_DECLTYPE( 1.f / int() ,type);

  type x = 1.f;
}
