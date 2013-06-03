//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_sincos.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/pio2_3.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/fast_sin.hpp>
#include <nt2/include/functions/fast_cos.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( fast_sincos, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::fast_sincos;
  using nt2::tag::fast_sincos_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT a[] = {nt2::Zero<vT>(), nt2::One<vT>(), nt2::Pio2_3<vT>(), nt2::Pi<vT>(),
            nt2::Pio_2<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  size_t N =  sizeof(a)/sizeof(vT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<fast_sincos_(vT)>::type)
                  , (std::pair<vT,vT>)
                  );

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      fast_sincos(a[i], s, c);
      NT2_TEST_EQUAL(s, nt2::fast_sin(a[i]));
      NT2_TEST_EQUAL(c, nt2::fast_cos(a[i]));
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = fast_sincos(a[i], c);
      NT2_TEST_EQUAL(s, nt2::fast_sin(a[i]));
      NT2_TEST_EQUAL(c, nt2::fast_cos(a[i]));
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = fast_sincos(a[i]);
      NT2_TEST_EQUAL(s, nt2::fast_sin(a[i]));
      NT2_TEST_EQUAL(c, nt2::fast_cos(a[i]));
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<vT,vT> p = fast_sincos(a[i]);
      NT2_TEST_EQUAL(p.first,  nt2::fast_sin(a[i]));
      NT2_TEST_EQUAL(p.second, nt2::fast_cos(a[i]));
    }
  }
}
