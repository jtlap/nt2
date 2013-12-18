//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/extensions.hpp>
#include <iostream>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/fastnormcdf.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/sqrt.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/memory/allocator.hpp>

using namespace nt2;

template <class A0>
BOOST_FORCEINLINE A0 blackandscholes(A0 const &a0, A0 const &a1, A0 const &a2, A0 const &a3, A0 const &a4)
{
  A0 da   = boost::simd::sqrt(a2);
  A0 tmp1 = nt2::log(a0/a1);
  A0 tmp2 = boost::simd::sqr(a4);
  A0 tmp4 = nt2::fma(tmp2,nt2::Half<A0>(),a3);
  A0 tmp3 = (tmp4*a2)/(a4*da);
  A0 ed   = nt2::exp(-a3*a2);
  A0 d1   = tmp1 + tmp3;
  A0 d2   = nt2::fma(-a4,da,d1);
  A0 fd1  = nt2::fastnormcdf(d1);
  A0 fd2  = nt2::fastnormcdf(d2);

  return a0*fd1 -a1 * ed * fd2;
}

template<typename T>
NT2_EXPERIMENT(blackandscholes_exp)
{
public:

  blackandscholes_exp( std::size_t const& n)
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , size_(n)
  {
    Sa.resize(size_);
    Xa.resize(size_);
    Ta.resize(size_);
    ra.resize(size_);
    va.resize(size_);
    R.resize(size_);

    for(i = 0; i <size_; ++i) Sa[i]=Xa[i]=Ta[i]=ra[i]=va[i]= T(i+1);
  }

  virtual void run() const
  {
    using boost::simd::pack;
    using boost::simd::native;
    using boost::simd::aligned_store;
    using boost::simd::aligned_load;

    typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> type;
    step_size_=boost::simd::meta::cardinal_of<type>::value;
    i=0;

    while (size_-i>=step_size_)
    {
      type Sa_tmp = aligned_load<type>(&Sa[i]);
      type Xa_tmp = aligned_load<type>(&Xa[i]);
      type Ta_tmp = aligned_load<type>(&Ta[i]);
      type ra_tmp = aligned_load<type>(&ra[i]);
      type va_tmp = aligned_load<type>(&va[i]);
      aligned_store(blackandscholes(Sa_tmp, Xa_tmp, Ta_tmp, ra_tmp, va_tmp),&R[i]);
      i += step_size_;
    }
    for (; i<size_; i++)
      R[i] += blackandscholes(Sa[i], Xa[i], Ta[i], ra[i], va[i]);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/(double(size_));
  }

  virtual void info(std::ostream& os) const { os << size_; }

  virtual void reset() const
  {}

 private:
  mutable std::vector<T, boost::simd::allocator<T> > Sa, Xa, Ta, ra, va, R;
  mutable std::size_t step_size_;
  std::size_t size_;
  mutable std::size_t i, j;
};

NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (13));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (32));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (64));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (128));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (256));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (512));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (1024));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (2048));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (20480));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (204800));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (1027*1024));
