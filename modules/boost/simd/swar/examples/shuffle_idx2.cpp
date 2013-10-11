#include <boost/simd/include/functions/shuffle.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <iostream>

using boost::simd::pack;
using boost::simd::shuffle;

int main()
{
  pack<float,4> f(1,2,3,4), g(10,20,30,40);

  // Generates [0 1 10 0]
  std::cout << shuffle<-1,0,4,-1>(f,g) << "\n";
}
