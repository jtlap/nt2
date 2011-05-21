#include <iostream>
#include <numeric>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/simd/begin.hpp>
#include <nt2/sdk/simd/end.hpp>
#include <nt2/include/timing.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/toolbox/constant/function/dsl/digits.hpp>
#include <nt2/toolbox/constant/function/dsl/true.hpp>
#include <nt2/toolbox/constant/function/dsl/false.hpp>
#include <nt2/toolbox/operator.hpp>

using namespace std;

template<class T> void bench(std::size_t sz)
{
    static volatile T r,vr;

    nt2::memory::buffer<T, nt2::memory::allocator<T> > b(0,sz);
    for(int i=0;i<sz;++i) b[i] = 1;

    nt2::ctic();
    for(int i=0;i<100000;++i) r = std::accumulate(b.begin(),b.end(),T(0));
    double d = nt2::ctoc(false);

    nt2::ctic();
    for(int i=0;i<100000;++i)
    {
      nt2::simd::pack<T> zz,itr;
      itr = std::accumulate( nt2::simd::begin(b),nt2::simd::end(b),zz);
      vr  = std::accumulate( itr.begin(),itr.end(),T(0));
     }
    double vd = nt2::ctoc(false);
    std::cout << d/vd << "\t";
}

int main()
{
  for(std::size_t i=2;i<=16384;i*=2)
  {
    std::cout << i << "\t";
    bench<double>(i);
    bench<float>(i);
    std::cout << "\n";
  }
}
