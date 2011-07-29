#include <iostream>
#include <nt2/sdk/memory/align_on.hpp>

using nt2::memory::align_on;

int main()
{
  std::cout << align_on<4>(0)     << std::endl;
  std::cout << align_on<4>(1)     << std::endl;
  std::cout << align_on<4>(11)    << std::endl;
  std::cout << align_on<4>(1337)  << std::endl;
}
