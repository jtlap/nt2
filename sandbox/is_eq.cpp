#include <iostream>
#include <nt2/include/simd.hpp>

using namespace nt2;
using namespace nt2::simd;

int main()
{
  native<nt2::int32_t,tag::sse_> x,y;
  std::cout << x << " " << y <<"\n";
  std::cout << nt2::eq(x,y) <<"\n";
}
