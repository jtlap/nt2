#include <iostream>
#include <nt2/sdk/details/bitwise_cast.hpp>

int main()
{
  float f = -1.f;
  std::cout << std::hex << nt2::bitwise_cast<unsigned int>(f) << "\n";
}
