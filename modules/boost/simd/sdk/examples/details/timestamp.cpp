#include <cstdio>
#include <nt2/sdk/details/timestamp.hpp>

int main()
{
  printf("Date: %s\n", nt2::timestamp().c_str());
}
