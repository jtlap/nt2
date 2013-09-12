#include <boost/simd/sdk/config/is_supported.hpp>

#include <iostream>
#include <cstddef>
#include <cstring>

using boost::simd::is_supported;
using namespace boost::simd::tag;

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <instruction_set>" << std::endl;
    return 1;
  }

  int b = is_supported(argv[1]);

  switch(b)
  {
    case  1 : std::cout << argv[1] << ": supported" << std::endl;
              return 0;
              break;

    case  0 : std::cerr << argv[1] << ": unknown instruction set" << std::endl;
              return 1;
              break;

    case -1:  std::cout << argv[1] << ": not supported" << std::endl;
              return 1;
              break;
  }

  return 1;
}
