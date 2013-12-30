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
      for(std::size_t i = 0; i<size_; ++i) X[i] = Y[i] = T(i);
    }

    virtual void run() const
    {
      for (std::size_t i = 0; i<size_; i++)
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

NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (float), (16384));

NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot_scalar, (double), (16384));
