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

#ifdef __ANDROID__
  #define TURBOFREQ 1.008000
#else
  #define TURBOFREQ 3.401
#endif
#define NOPS 2.0

template<typename T>
NT2_EXPERIMENT(Tdot_scalar)
{
  public:

    Tdot_scalar(std::size_t const& s)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
    size_(s)
    {
      X.resize(s); Y.resize(s);
      for(int i = 0; i<size_; ++i) X[i] = Y[i] = T(i);
    }

    virtual void run() const
    {
      for (int i = 0; i<size_; i++)
        res += X[i] * Y[i];
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
    mutable typename std::vector<T> X, Y;
};
typedef float K;
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (K), (16384));
