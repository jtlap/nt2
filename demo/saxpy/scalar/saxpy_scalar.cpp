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
#include <boost/simd/reduction/functions/sum.hpp>
//#define TURBOFREQ 3.401
#define TURBOFREQ 1.008000
#define NOPS 2.0

template<typename T> 
NT2_EXPERIMENT(Taxpy)
{
  public:   
    
    Taxpy(std::size_t const& s, T const& a) 
    : NT2_EXPRIMENT_CTOR(1., "GFLOPS"),
    size_(s), alpha(a)
    {

      X.resize(s); Y.resize(s);
      for(int i = 0; i<size_; ++i) X[i] = Y[i] = T(i);
    }

    inline T Taxpy_scalar(std::size_t const& s) const
    {   
      #pragma simd
      for(int i = 0; i<size_; i++)
      {
        Y[i] = Y[i] + alpha*(X[i]);
      }
    }
    virtual void run() const
    {
      Taxpy_scalar(size_);
    }
    virtual double compute(nt2::benchmark_result_t const& r) const
    { 
    //  return r.first/double(size_);
     // printf("%e\n",r.first );
            return(double(size_)*NOPS*TURBOFREQ/r.first);
    }

    virtual void info(std::ostream& os) const { os << size_; }
   
    virtual void reset() const 
    {
    }
  private:
    T alpha;
    std::size_t size_;
    mutable typename std::vector<T> X, Y;
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