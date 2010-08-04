#include <iostream>
#include <nt2/sdk/aligned/is_aligned.hpp>

using nt2::aligned::is_aligned;

int main()
{
  std::cout << is_aligned<4>(0)     << std::endl;
  std::cout << is_aligned<4>(1)     << std::endl;
  std::cout << is_aligned<4>(12)    << std::endl;
  std::cout << is_aligned<4>(1337)  << std::endl;
}
