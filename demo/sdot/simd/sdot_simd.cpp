//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
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

#ifdef __ANDROID__
  #define TURBOFREQ 1.008000
#else
  #define TURBOFREQ 3.401
#endif

#define NOPS 2.0

template <class A0>
BOOST_FORCEINLINE __attribute__((flatten)) A0 Tdot_work(A0 const& X, A0 const& Y)
{
  return(X*Y);
}

template<typename T>
NT2_EXPERIMENT(Tdot_simd)
{
  public:

    Tdot_simd(std::size_t const& s)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
    size(s)
    {
      X.resize(s); Y.resize(s);
      for(std::size_t i = 0; i<size; ++i) X[i] = Y[i] = T(i);
    }

    virtual void run() const
    {
      using boost::simd::pack;
      using boost::simd::native;
      using boost::simd::aligned_store;
      typedef pack<T> type;
      step_size = boost::simd::meta::cardinal_of<type>::value;
      type res_pack = type(0.);
      for (std::size_t i = 0; i<size; i+=step_size){
        type X_pack(&X[i]);
        type Y_pack(&Y[i]);
        res_pack += Tdot_work(X_pack, Y_pack);
      }
      res = boost::simd::sum(res_pack);
    }
    virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size)*NOPS*TURBOFREQ/r.first);
    }

    virtual void info(std::ostream& os) const { os << size; }

    virtual void reset() const
    {
    }
  private:
    mutable T res;
    std::size_t size;
    mutable std::size_t step_size;
    mutable typename std::vector<T, boost::simd::allocator<T> > X, Y;
};
typedef float K;
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot_simd, (K), (16384));
