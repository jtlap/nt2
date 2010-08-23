#include <windows.h>
#include <stdio.h>

int main()
{
  SYSTEM_INFO sysinfo;
  GetSystemInfo( &sysinfo );
  return sysinfo.dwNumberOfProcessors;
}
