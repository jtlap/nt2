#include <iostream>
#include <nt2/sdk/config/compiler.hpp>

int main()
{
  #ifdef NT2_COMPILER_DETECTED
  std::cout << "Current compiler : " << NT2_COMPILER_STRING << std::endl;
  #endif
}

