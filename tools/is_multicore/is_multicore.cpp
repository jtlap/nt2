#include <boost/simd/sdk/config/details/detector/cpuid.hpp>
#include <boost/simd/sdk/config/details/detector/get_vendor.hpp>
#include <cassert>

int get_byte(int reg, int pos)
{
  const int dec = pos * 8;
  return ((reg & (0x000000FF << dec)) >> dec);
}

int  get_range(int reg, int begin, int end)
{
  int mask=0x00000000;
  assert( begin < end );
  for(int i = 0; i < (end - begin); i++) { mask <<= 1; mask |= 0x1; }
  return ((reg >> begin) & mask);
}

int get_threads()
{
  int regs[4];
  boost::simd::config::x86::cpuidex(regs, 0x0000000B, 0x00000000);
  return get_range(regs[1], 0, 16);
}

int get_logical_cores()
{
  int regs[4];
  boost::simd::config::x86::cpuid(regs, 0x00000000);
  if(boost::simd::config::x86::get_vendor() == boost::simd::config::x86::intel)
  {
    boost::simd::config::x86::cpuidex(regs, 0x0000000B, 0x00000001);
    return get_range(regs[1], 0, 16);
  }
  else if(boost::simd::config::x86::get_vendor() == boost::simd::config::x86::amd)
  {
    boost::simd::config::x86::cpuid(regs, 0x00000001);
    return (get_range(regs[1], 16, 24));
  }
  else //Intel by default
  {
    boost::simd::config::x86::cpuidex(regs, 0x0000000B, 0x00000001);
    return get_range(regs[1], 0, 16);
  }
}

int get_physical_cores()
{
  int regs[4];
  boost::simd::config::x86::cpuid(regs, 0x00000000);
  if(boost::simd::config::x86::get_vendor() == boost::simd::config::x86::intel)
  {
    return (get_logical_cores()/get_threads());
  }
  else if(boost::simd::config::x86::get_vendor() == boost::simd::config::x86::amd)
  {
    boost::simd::config::x86::cpuid(regs, 0x80000008);
    return (get_byte(regs[2], 0) + 1);
  }
  else return -1;
}


int main(int argc, char *argv[])
{
  return get_physical_cores();
}
