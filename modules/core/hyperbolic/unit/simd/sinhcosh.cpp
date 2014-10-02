//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/sinhcosh.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(sinhcosh, NT2_SIMD_REAL_TYPES)
{
  using nt2::sinhcosh;
  using nt2::tag::sinhcosh_;
  using boost::simd::native;
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT a[] = {nt2::Zero<vT>(), nt2::Half<vT>(), nt2::One<vT>(), nt2::splat<vT>(-5), nt2::splat<vT>(5)};
  size_t N =  sizeof(a)/sizeof(vT);
  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<sinhcosh_(vT)>::type)
                  , (std::pair<vT,vT>)
                  );

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      sinhcosh(a[i], s, c);
      NT2_TEST_ULP_EQUAL(s, nt2::sinh(a[i]), 1);
      NT2_TEST_ULP_EQUAL(c, nt2::cosh(a[i]), 1);
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = sinhcosh(a[i], c);
      NT2_TEST_ULP_EQUAL(s, nt2::sinh(a[i]), 1);
      NT2_TEST_ULP_EQUAL(c, nt2::cosh(a[i]), 1);
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = sinhcosh(a[i]);
      NT2_TEST_ULP_EQUAL(s, nt2::sinh(a[i]), 1);
      NT2_TEST_ULP_EQUAL(c, nt2::cosh(a[i]), 1);
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<vT,vT> p = sinhcosh(a[i]);
      NT2_TEST_ULP_EQUAL(p.first,  nt2::sinh(a[i]), 1);
      NT2_TEST_ULP_EQUAL(p.second, nt2::cosh(a[i]), 1);
    }
  }

#ifndef BOOST_SIMD_NO_INVALIDS
  vT b[] = {nt2::splat<vT>(10), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  N =  sizeof(b)/sizeof(vT);
  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      sinhcosh(b[i], s, c);
      NT2_TEST_ULP_EQUAL(s, nt2::sinh(b[i]), 1);
      NT2_TEST_ULP_EQUAL(c, nt2::cosh(b[i]), 1);
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = sinhcosh(b[i], c);
      NT2_TEST_ULP_EQUAL(s, nt2::sinh(b[i]), 1);
      NT2_TEST_ULP_EQUAL(c, nt2::cosh(b[i]), 1);
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = sinhcosh(b[i]);
      NT2_TEST_ULP_EQUAL(s, nt2::sinh(b[i]), 1);
      NT2_TEST_ULP_EQUAL(c, nt2::cosh(b[i]), 1);
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<vT,vT> p = sinhcosh(b[i]);
      NT2_TEST_ULP_EQUAL(p.first,  nt2::sinh(b[i]), 1);
      NT2_TEST_ULP_EQUAL(p.second, nt2::cosh(b[i]), 1);
    }
  }
#endif


}
