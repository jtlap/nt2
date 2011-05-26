#include <iostream>
#include <numeric>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/simd/begin.hpp>
#include <nt2/sdk/simd/end.hpp>
#include <nt2/include/timing.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/toolbox/constant/constants/dsl/digits.hpp>
#include <nt2/toolbox/reduction.hpp>
#include <nt2/toolbox/operator.hpp>
#include <nt2/toolbox/arithmetic/include/tofloat.hpp>

using namespace std;

template<class T> void bench(std::size_t sz)
{
    static volatile T r,vr;

    nt2::memory::buffer<T, nt2::memory::allocator<T> > b(0,sz);
    for(std::size_t i=0;i<sz;++i) b[i] = 1;

    nt2::ctic();
    for(std::size_t i=0;i<100000;++i) r = std::accumulate(b.begin(),b.end(),T(0));
    double d = nt2::ctoc(false);

    nt2::ctic();
    for(std::size_t i=0;i<100000;++i)
    {
      nt2::simd::pack<T> zz;
      vr = nt2::sum(std::accumulate( nt2::simd::begin(b),nt2::simd::end(b),zz));
     }
    double vd = nt2::ctoc(false);
    std::cout << d/vd << "\t";
}

#include <nt2/sdk/details/type_id.hpp>

int main()
{/*
  for(std::size_t i=2;i<=16384;i*=2)
  {
    std::cout << i << "\t";
    bench<double>(i);
    bench<float>(i);
    std::cout << "\n";
  }
  */

  nt2::simd::pack<float> u(4.64f), r;
  nt2::simd::pack<int> v(3);

  r = nt2::tofloat(v);
  std::cout << r << "\n";

  r = u + nt2::tofloat(v);
  std::cout << r << "\n";

  r = nt2::tofloat(v+2)*nt2::ten_;
  std::cout << r << "\n";

}
