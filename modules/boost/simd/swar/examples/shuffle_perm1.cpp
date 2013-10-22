#include <boost/simd/include/functions/shuffle.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>

using boost::mpl::int_;
using boost::simd::pack;
using boost::simd::shuffle;

struct even_odd
{
  template<class Index, class Cardinal>
  struct apply  : int_< Index::value < Cardinal::value/2
                      ? Index::value * 2
                      : (Index::value-Cardinal::value/2) * 2 + 1
                      >
  {};
};

int main()
{
  pack<float,4> f(1,2,3,4);

  // Gather even and odd indexes on the side: [ 1 3 2 4 ]
  std::cout << shuffle<even_odd>(f) << "\n";
}
