#include <iostream>
#include <nt2/include/simd.hpp>

using namespace std;
using namespace nt2;
using namespace nt2::simd;

int main()
{
  native<nt2::uint64_t, tag::sse_> x = {{2,4}};

  cout << x*x << endl;
}
