//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/unit/details/prng.hpp>

#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>

#include <nt2/sdk/bench/protocol/max_duration.hpp>

#include <nt2/sdk/bench/setup/geometric.hpp>

#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/muls.hpp>
#include <boost/simd/include/functions/muls.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/constants/zero.hpp>

#include <vector>

using namespace nt2::bench;
using namespace nt2;

template <class A0>
BOOST_FORCEINLINE A0 Tdot_work(A0 const& X, A0 const& Y)
{
  return(X*Y);
}

template<typename T> struct sdot_simd
{
    typedef void experiment_is_immutable;
  sdot_simd(std::size_t n)
                  :  size_(n)
  {
    X.resize(size_); Y.resize(size_);
    for(std::size_t i = 0; i<size_; ++i)
      X[i] = Y[i] = T(i);
  }

  void operator()()
  {
    using boost::simd::native;
    using boost::simd::aligned_load;
    using boost::simd::aligned_store;

    typedef native<T, BOOST_SIMD_DEFAULT_EXTENSION> type;
    step_size = boost::simd::meta::cardinal_of<type>::value;
    type res_pack = boost::simd::Zero<type>();
    for (std::size_t i = 0; i<size_; i+=step_size){
      type X_pack = aligned_load<type>(&X[i]);
      type Y_pack = aligned_load<type>(&Y[i]);
      res_pack += Tdot_work(X_pack, Y_pack);
    }
    res_ = boost::simd::sum(res_pack);
  }

  friend std::ostream& operator<<(std::ostream& os, sdot_simd<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_ ; }
  std::size_t flops() const { return 2 ; }

  private:
    T res_;
    std::size_t size_, step_size;
    typename std::vector<T, boost::simd::allocator<T> > X, Y;
};

NT2_REGISTER_BENCHMARK_TPL( sdot_simd, (float)(double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 2);

  run_during_with< sdot_simd<T> > ( 1.
                                      , geometric(size_min,size_max,size_step)
                                      , gflops<stat::median_>()
                                      );
}
