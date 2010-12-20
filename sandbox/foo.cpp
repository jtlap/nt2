#include <iostream>
#include <nt2/sdk/simd/io.hpp>
#include <nt2/sdk/simd/native.hpp>

using namespace std;
using namespace nt2;
using namespace nt2::simd;

int main()
{
   cout << True< native<float,tag::sse_> >() << "\n";
   cout << False< native<float,tag::sse_> >() << "\n";
}
