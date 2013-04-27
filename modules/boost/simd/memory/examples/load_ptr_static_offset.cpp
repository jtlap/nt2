#include <iostream>
#include <boost/simd/include/functions/load.hpp>

using boost::simd::load;

int main()
{
  float data[] = { 1, 2, 3, 4 };
  std::cout << load<float,-2>(&data[3], 2)     << std::endl;
  std::cout << load<float,-3>(&data[3], 2)     << std::endl;
  std::cout << load<float, 0>(&data[3],-2)     << std::endl;
  std::cout << load<float,-2>(&data[3],-1)     << std::endl;
}
