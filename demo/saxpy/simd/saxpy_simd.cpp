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
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <nt2/include/functions/aligned_store.hpp>

#ifdef __ANDROID__
  #define TURBOFREQ 1.008000
#else
  #define TURBOFREQ 3.401
#endif
#define NOPS 2.0

template <class A0, class A1>
BOOST_FORCEINLINE __attribute__((flatten)) A0 Taxpy_work(A1 const& alpha, A0 const& X, A0 &Y)
{
  return(boost::simd::fma(alpha, X, Y));
}

template<typename T>
NT2_EXPERIMENT(Taxpy_simd)
{
  public:

    Taxpy_simd(std::size_t const& s, T const& a)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
      alpha(a), size_(s)
    {
      X.resize(s); Y.resize(s);
      for(std::size_t i = 0; i<size_; ++i) X[i] = Y[i] = T(i);
    }

    virtual void run() const
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
    virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size_)*NOPS*TURBOFREQ/r.first);
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

NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (16,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (32,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (64,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (128,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (256,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (512,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (1024,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (2048,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (4096,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (8192,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (16384,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (float), (163840,2.7f));

NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (16,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (32,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (64,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (128,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (256,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (512,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (1024,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (2048,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (4096,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (8192,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (16384,2.7));
NT2_RUN_EXPERIMENT_TPL( Taxpy_simd, (double), (163840,2.7));
