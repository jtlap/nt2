#include <windwos.h>

int main()
{
  SYSTEM_INFO sysinfo;
  GetSystemInfo( &sysinfo );

  return sysinfo.dwNumberOfProcessors;
}
