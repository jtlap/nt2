#include <iostream>
#include <nt2/sdk/details/preprocessor.hpp>

int main()
{
  std::cout << NT2_PP_DEBUG( NT2_PP_STRIP(no parens) ) << std::endl;
  std::cout << NT2_PP_DEBUG( NT2_PP_STRIP((with parens)) ) << std::endl;
}
