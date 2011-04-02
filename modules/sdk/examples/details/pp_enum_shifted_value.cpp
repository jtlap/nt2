#include <iostream>
#include <nt2/sdk/details/preprocessor.hpp>

int main()
{
  // Prints (6 , 6 , 6 , 6)
  std::cout << NT2_PP_DEBUG( NT2_PP_ENUM_SHIFTED_VALUE(5,6) ) << std::endl;
}
