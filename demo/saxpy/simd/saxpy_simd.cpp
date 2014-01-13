//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
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
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>

#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>

#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <nt2/include/functions/aligned_store.hpp>

#include <boost/fusion/include/at.hpp>

#include <vector>

using namespace nt2::bench;
using namespace nt2;

template <class A0, class A1>
BOOST_FORCEINLINE A0 Taxpy_work(A1 const& alpha, A0 const& X, A0 &Y)
{
  return(boost::simd::fma(alpha, X, Y));
}

template<typename T> struct axpy_simd
{
  template<typename Setup>
  axpy_simd(Setup const& s)
              :  size_(boost::fusion::at_c<0>(s))
              ,  alpha(boost::fusion::at_c<1>(s))
  {
    X.resize(size_); Y.resize(size_);
    for(std::size_t i = 0; i<size_; ++i)
      X[i] = Y[i] = T(i);
  }

  void operator()()
  {
    using boost::simd::pack;
    using boost::simd::native;
    using boost::simd::aligned_store;
    typedef pack<T> type;
    step_size_ = boost::simd::meta::cardinal_of<type>::value;
    for (std::size_t i = 0; i<size_; i+=step_size_)
    {
      type X_pack(&X[i]);
      type Y_pack(&Y[i]);
      aligned_store(Taxpy_work(alpha, X_pack, Y_pack),&Y[i]);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, axpy_simd<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_ ; }
  std::size_t flops() const { return 2 ; }

  private:
    T alpha;
    std::size_t size_, step_size_;
    typename std::vector<T, boost::simd::allocator<T> > X, Y;
};

NT2_REGISTER_BENCHMARK_TPL( axpy_simd, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 2);

  T alpha = args("alpha", 1.);

  run_during_with< axpy_simd<T> > ( 1.
                                  , and_( geometric(size_min,size_max,size_step)
                                        , constant(alpha)
                                  )
                                  , gflops<stat::median_>()
                                  );
}
