#include <iostream>
#include <nt2/include/native.hpp>

using namespace std;
using namespace nt2;
using namespace nt2::simd;

int main()
{
  native<float, tag::sse_> x = {{2,4,4,6}};

  cout << True< native<float, tag::sse_> >() << endl;
  cout << True< native<double, tag::sse_> >() << endl;
}
