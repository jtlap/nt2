#include <cstdio>
#include <nt2/sdk/sys/timestamp.hpp>

int main()
{
  printf("Date: %s\n", nt2::sys::timestamp().c_str());
}
