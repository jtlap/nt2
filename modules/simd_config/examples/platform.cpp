#include <iostream>
#include <nt2/sdk/config/os.hpp>

int main()
{
  #ifdef NT2_OS_DETECTED
  std::cout << "Current OS : " << NT2_OS_STRING << std::endl;
  #endif
}


