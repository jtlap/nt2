#include <boost/simd/include/functions/shuffle.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>

using boost::mpl::int_;
using boost::simd::pack;
using boost::simd::shuffle;

struct half_half
{
  template<class Index, class Cardinal>
  struct apply  : int_< Index::value < Cardinal::value/2
                      ? Index::value
                      : Index::value+Cardinal::value
                      >
  {};
};

int main()
{
  pack<float,4> f(1,2,3,4), g(10,20,30,40);

  // Gather the first half of f and the second half of g: [1 2 30 40]
  std::cout << shuffle<half_half>(f,g) << "\n";
}
