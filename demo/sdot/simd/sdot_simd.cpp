//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <vector>
#include <nt2/sdk/bench/benchmark.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/muls.hpp>
#include <boost/simd/include/functions/muls.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/sum.hpp>

#define TURBOFREQ 3.401
#define NOPS 2.0

template <class A0>
BOOST_FORCEINLINE __attribute__((flatten)) A0 Tdot_simd(A0 const& X, A0 const& Y)
{
  return(X*Y);
}

template<typename T>
NT2_EXPERIMENT(Tdot)
{
  public:

    Tdot(std::size_t const& s)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
    size_(s)
    {
      X.resize(s); Y.resize(s);
      for(int i = 0; i<size_; ++i) X[i] = Y[i] = T(i);
    }

    virtual void run() const
    {
      using boost::simd::pack;
      using boost::simd::native;
      using boost::simd::aligned_store;
      typedef pack<T> type;
      step_size_ = boost::simd::meta::cardinal_of<type>::value;
      type res_pack = type(0.);
      for (int i = 0; i<size_; i+=step_size_){
        type X_pack(&X[i]);
        type Y_pack(&Y[i]);
        res_pack += Tdot_simd(X_pack, Y_pack);
      }
      res = boost::simd::sum(res_pack);//, step_size_);
    }
    virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size_)*NOPS*TURBOFREQ/r.first);
    }

    virtual void info(std::ostream& os) const { os << size_; }

    virtual void reset() const
    {
    }
  private:
    mutable T res;
    std::size_t size_;
    mutable std::size_t step_size_;
    mutable typename std::vector<T, boost::simd::allocator<T> > X, Y;
};
typedef float K;
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot, (K), (16384));
//NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (163840));
