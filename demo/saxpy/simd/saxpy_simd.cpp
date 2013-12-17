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
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <nt2/include/functions/aligned_store.hpp>

#define TURBOFREQ 3.401
#define NOPS 2.0
#define NUM_ITER 1e5

template <class A0, class A1>
BOOST_FORCEINLINE __attribute__((flatten)) A0 Taxpy_simd(A1 const& alpha, A0 const& X, A0 &Y)
{
  return(boost::simd::fma(alpha, X, Y));
}

template<typename T>
NT2_EXPERIMENT(Taxpy)
{
  public:

    Taxpy(std::size_t const& s, T const& a)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
    size_(s), alpha(a)
    {
      X.resize(s); Y.resize(s);
      for(int i = 0; i<size_; ++i) X[i] = Y[i] = T(i);
    }

    virtual void run() const
    {
      for (int j=0;j<NUM_ITER;j++){
      using boost::simd::pack;
      using boost::simd::native;
      using boost::simd::aligned_store;
      typedef pack<T> type;
      step_size_ = boost::simd::meta::cardinal_of<type>::value;
      for (int i = 0; i<size_; i+=step_size_){
        type X_pack(&X[i]);
        type Y_pack(&Y[i]);
        aligned_store(Taxpy_simd(alpha, X_pack, Y_pack),&Y[i]);
      }
    }
    }
    virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size_)*NOPS*TURBOFREQ/r.first*NUM_ITER);
    }

    virtual void info(std::ostream& os) const { os << size_; }

    virtual void reset() const
    {
    }
  private:
    T alpha;
    std::size_t size_;
    mutable std::size_t step_size_;
    mutable typename std::vector<T, boost::simd::allocator<T> > X, Y;
};
typedef float K;
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (16,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (32,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (64,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (128,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (256,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (512,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (1024,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (2048,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (4096,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (8192,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (16384,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy, (K), (163840,2.7f));
