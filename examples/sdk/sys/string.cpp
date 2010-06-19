#include <cstdio>
#include <nt2/sdk/sys/string.hpp>

int main()
{
  nt2::sys::string empty;
  nt2::sys::string hello("Hello %s (%d)\n", "world", 0);

  empty = hello;

  printf("String was: %s", empty.c_str());
}
