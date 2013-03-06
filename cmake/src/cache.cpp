//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

int gcd(int a, int b )
{
  if(b == 0) return a; else return gcd(b, a%b);
}

int lcm(int a, int b )
{
  if(b ==0) return 0;
  return (a*b)/gcd(a,b);
}

#if defined(__GNUC__)
#include <fstream>

void getcachesizes(int& L1, int& L2, int& L3)
{
  int value;
  std::ifstream level1("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size");
  std::ifstream level2("/sys/devices/system/cpu/cpu1/cache/index1/coherency_line_size");
  std::ifstream level3("/sys/devices/system/cpu/cpu2/cache/index2/coherency_line_size");

  if(level1.is_open()) level1 >> L1;
  if(level2.is_open()) level2 >> L2;
  if(level3.is_open()) level3 >> L3;
}

#elif defined(_MSC_VER)
#include <windows.h>
#include <malloc.h>

typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,PDWORD);

void getcachesizes(int& L1, int& L2, int& L3)
{
  LPFN_GLPI glpi;
  BOOL done = FALSE;
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
  DWORD returnLength = 0;
  DWORD processorL1CacheCount = 0;
  DWORD processorL2CacheCount = 0;
  DWORD processorL3CacheCount = 0;
  DWORD byteOffset = 0;
  PCACHE_DESCRIPTOR Cache;

  glpi = (LPFN_GLPI) GetProcAddress(GetModuleHandle(TEXT("kernel32")),"GetLogicalProcessorInformation");
  if (NULL == glpi)
  {
    L1 = L2 = L3 = 16;
    return;
  }

  while (!done)
  {
    DWORD rc = glpi(buffer, &returnLength);

    if (FALSE == rc)
    {
      if (buffer) free(buffer);
      buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
    }
    else
    {
      done = TRUE;
    }
  }

  ptr = buffer;

  while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
  {
    if(ptr->Relationship == RelationCache)
    {
      Cache = &ptr->Cache;
      if (Cache->Level == 1)       L1 = (Cache->LineSize > 0) ?  Cache->LineSize  : 1;
      else if (Cache->Level == 2)  L2 = (Cache->LineSize > 0) ?  Cache->LineSize  : 1;
      else if (Cache->Level == 3)  L3 = (Cache->LineSize > 0) ?  Cache->LineSize  : 1;
    }
    byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    ptr++;
  }

  free(buffer);
}
#endif

int main()
{
  int L1(1),L2(1),L3(1);
  getcachesizes(L1,L2,L3);
  return lcm( L3, lcm(L2,L1) );
}

