#include <boost/simd/sdk/config/details/detector/cpuid.hpp>
#include <cstdio>

int main()
{
  int regs[4];
  boost::simd::config::x86::cpuid(regs, 1);
  int family = ((regs[0] & 0xF00000) >> 16) + ((regs[0] & 0xF00) >> 8);
  int model =  ((regs[0] & 0xF0000) >> 12) + ((regs[0] & 0xF0) >> 4);
  std::printf("%02X_%02X\n", family, model);
}

