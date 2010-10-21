#include <iostream>
#include <nt2/sdk/constant/real.hpp>

int main()
{
  std::cout << std::boolalpha << bool(nt2::Nan<float>() == true)<< "\n";
}
