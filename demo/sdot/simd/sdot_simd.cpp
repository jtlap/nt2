//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <vector>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template <class A0>
BOOST_FORCEINLINE A0 Tdot_work(A0 const& X, A0 const& Y)
{
  return(X*Y);
}

template<typename T> struct dot_simd
{
    typedef void experiment_is_immutable;
  dot_simd(std::size_t n)
                  :  size_(n)
  {
    X.resize(size_); Y.resize(size_);
    for(std::size_t i = 0; i<size_; ++i)
      X[i] = Y[i] = T(i);
  }

  void operator()()
  {
    using boost::simd::pack;
    using boost::simd::aligned_load;

    typedef pack<T> type;
    std::size_t step_size = boost::simd::meta::cardinal_of<type>::value;
    type res_pack = boost::simd::Zero<type>();
    for (std::size_t i = 0; i<size_; i+=step_size)
    {
      type X_pack = aligned_load<type>(&X[i]);
      type Y_pack = aligned_load<type>(&Y[i]);
      res_pack += X_pack * Y_pack;
    }
    res_ = boost::simd::sum(res_pack);
  }

  friend std::ostream& operator<<(std::ostream& os, dot_simd<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  double flops() const { return 2.*size_; }

private:
  T res_;
  std::size_t size_;
  typename std::vector<T, boost::simd::allocator<T> > X, Y;
};

NT2_REGISTER_BENCHMARK_TPL( dot_simd, NT2_SIMD_REAL_TYPES )
{
  std::size_t size_min  = args("size_min",   16*16);
  std::size_t size_max  = args("size_max", 4096*4096);
  std::size_t size_step = args("size_step",   4*4);

  run_during_with< dot_simd<T> > ( 1.
                                  , geometric(size_min,size_max,size_step)
                                  , gflops<stats::median_>()
                                  );
}
