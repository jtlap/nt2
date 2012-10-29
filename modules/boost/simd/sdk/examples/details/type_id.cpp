#include <vector>
#include <iostream>
#include <boost/simd/sdk/details/type_id.hpp>

int main()
{
  std::cout << boost::simd::type_id("some litteral string") << std::endl;
  std::cout << boost::simd::type_id(3.14159f) << std::endl;
  std::cout << boost::simd::type_id< std::vector<long*> >() << std::endl << std::endl;
}
