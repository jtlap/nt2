#include <boost/simd/include/functions/shuffle.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <iostream>

using boost::simd::pack;
using boost::simd::shuffle;

int main()
{
  pack<float,4> f(1,2,3,4);

  // Broadcast the 3rd element: [3 3 3 3]
  std::cout << shuffle<2,2,2,2>(f) << "\n";
}
