/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#include <iostream>
#include <string>

enum { eax,ebx,ecx,edx };

#if defined(__GNUC__)
void __cpuid( int CPUInfo[4],int InfoType)
{
  __asm__ __volatile__
  (
    "cpuid":\
    "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
  , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
  : "a" (InfoType)
  );
}

void __cpuidex(int CPUInfo[4],int InfoType,int ECXValue)
{
  __asm__ __volatile__
  (
    "cpuid":\
    "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
  , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
  : "a" (InfoType), "c" (ECXValue)
  );
}

#elif defined(_MSC_VER)
#include <intrin.h>
#endif

bool has_bit_set(int value, int bit)
{
  return (value & (1<<bit)) != 0;
}

struct matcher
{
  int function,reg,bit;
}
options[] =
{
    {0x00000001,edx,23} // MMX
  , {0x00000001,edx,25} // SSE
  , {0x00000001,edx,26} // SSE2
  , {0x00000001,ecx,0} // SSE3
  , {0x00000001,ecx,9} // SSSE3
  , {0x00000001,ecx,19} // SSE4.1
  , {0x00000001,ecx,20} // SSE4.2
  , {0x00000001,ecx,28} // AVX
  , {0x80000001,edx,11} // XOP
  , {0x80000001,edx,16} // FMA
};

int main(int argc, char** argv)
{
  int registers[4];
  if(argc < 2) return -1;

  std::string target(argv[1]);
  __cpuid(registers,0x00000000);

  matcher m;

       if(target == "mmx"    ) m = options[0];
  else if(target == "sse"    ) m = options[1];
  else if(target == "sse2"   ) m = options[2];
  else if(target == "sse3"   ) m = options[3];
  else if(target == "ssse3"  ) m = options[4];
  else if(target == "sse4.1" ) m = options[5];
  else if(target == "sse4.2" ) m = options[6];
  else if(target == "avx"    ) m = options[7];
  else if(target == "xop"    ) m = options[8];
  else if(target == "fma4"   ) m = options[9];

  __cpuid(registers,m.function);
  return has_bit_set(registers[m.reg],m.bit);
}
