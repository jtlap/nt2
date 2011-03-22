#include <iostream>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/include/functions/is_nan.hpp>

using nt2::meta::from_bits;
using nt2::is_nan;

int main()
{
  from_bits<float>::type f;
  f.bits = 0xFFFFFFFF;
    
  std::cout << is_nan(f.value) << " ? " << f.value << std::endl;
  
  f.value = 1.0f;
  std::cout << std::hex << f.bits << std::endl;
}
