//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/fastnormcdf.hpp>
#include <boost/simd/include/functions/sqrt.hpp>
#include <boost/simd/include/functions/fma.hpp>

template <class A0>
BOOST_FORCEINLINE A0 blackandscholes(A0 const &a0, A0 const &a1, A0 const &a2, A0 const &a3, A0 const &a4)
{
  A0 da   = boost::simd::sqrt(a2);
  A0 tmp1 = nt2::log(a0/a1);
  A0 tmp2 = a4*a4;
  A0 tmp4 = boost::simd::fma(tmp2,nt2::Half<A0>(),a3);
  A0 tmp3 = (tmp4*a2)/(a4*da);
  A0 ed   = nt2::exp(-a3*a2);
  A0 d1   = tmp1 + tmp3;
  A0 d2   = nt2::fma(-a4,da,d1);
  A0 fd1  = nt2::fastnormcdf(d1);
  A0 fd2  = nt2::fastnormcdf(d2);
  return a0*fd1 -a1 * ed * fd2;
}

template<typename T>
NT2_EXPERIMENT(blackandscholes_scalar)
{
public:
  typedef T value_type;

  blackandscholes_scalar( std::size_t const& n)
  : NT2_EXPERIMENT_CTOR(.1f, "cycles/elements")
  , size_(n)
  {
    Sa.resize(size_);
    Xa.resize(size_);
    Ta.resize(size_);
    ra.resize(size_);
    va.resize(size_);
    R.resize(size_);

    for(int i = 0; i < size_; ++i) Sa[i]=Xa[i]=Ta[i]=ra[i]=va[i]= value_type(i+1);
  }

  virtual void run() const
  {
    for (int ii=0;ii<size_;ii++)
      R[ii] = blackandscholes(Sa[ii], Xa[ii], Ta[ii], ra[ii], va[ii]);
    }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(size_);
  }

  virtual void info(std::ostream& os) const { os << size_; }

  virtual void reset() const
  {
  }

 private:
  mutable std::vector<value_type> Sa, Xa, Ta, ra, va, R;

  std::size_t size_;
};

NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (16));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (32));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (64));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (128));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (256));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (512));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (1024));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (2048));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (20480));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (204800));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_scalar, (float), (1024*1024));
