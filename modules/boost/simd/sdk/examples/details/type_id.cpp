#include <vector>
#include <iostream>
#include <nt2/sdk/details/type_id.hpp>

int main()
{
  std::cout << nt2::type_id("some litteral string") << std::endl;
  std::cout << nt2::type_id(3.14159f) << std::endl;
  std::cout << nt2::type_id< std::vector<long*> >() << std::endl << std::endl;
}
