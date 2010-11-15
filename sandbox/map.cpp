#include <iostream>
#include <nt2/include/simd.hpp>

using namespace std;
using namespace nt2;
using namespace nt2::simd;

int main()
{
  native<float, tag::sse_> x = {{2,4,4,6}};

  cout << (~x) << endl;
  cout << x/x << endl;
}
