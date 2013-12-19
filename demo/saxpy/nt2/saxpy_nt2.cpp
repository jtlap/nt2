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
#include <nt2/include/functions/fma.hpp>
#include <nt2/table.hpp>

#ifdef __ANDROID__
  #define TURBOFREQ 1.008000
#else
  #define TURBOFREQ 3.401
#endif
#define NOPS 2.0

template<typename T>
NT2_EXPERIMENT(Taxpy_nt2)
{
  public:

    Taxpy_nt2(std::size_t const& s, T const& a)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
      alpha(a), size(s)
    {
      X.resize(nt2::of_size(s)); Y.resize(nt2::of_size(s));
      for(std::size_t i = 1; i<=size; ++i) X(i) = Y(i) = T(i-1);
    }

    virtual void run() const
    {
      Y = nt2::fma(alpha, X, Y);
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
    T alpha;
    std::size_t size;
    mutable nt2::table<T> X, Y;
};
typedef float K;
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (16,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (32,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (64,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (128,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (256,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (512,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (1024,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (2048,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (4096,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (8192,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (16384,2.7f));
NT2_RUN_EXPERIMENT_TPL( Taxpy_nt2, (K), (163840,2.7f));
