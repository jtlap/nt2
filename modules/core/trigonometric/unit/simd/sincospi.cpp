//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sincospi.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( sincospi, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::sincospi;
  using nt2::tag::sincospi_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT a[] = {nt2::Zero<vT>(), nt2::Invpi<vT>(), nt2::Third<vT>(), nt2::One<vT>(),
            nt2::Half<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  size_t N =  sizeof(a)/sizeof(vT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<sincospi_(vT)>::type)
                  , (std::pair<vT,vT>)
                  );

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      sincospi(a[i], s, c);
      NT2_TEST_EQUAL(s, nt2::sinpi(a[i]));
      NT2_TEST_EQUAL(c, nt2::cospi(a[i]));
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = sincospi(a[i], c);
      NT2_TEST_EQUAL(s, nt2::sinpi(a[i]));
      NT2_TEST_EQUAL(c, nt2::cospi(a[i]));
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = sincospi(a[i]);
      NT2_TEST_EQUAL(s, nt2::sinpi(a[i]));
      NT2_TEST_EQUAL(c, nt2::cospi(a[i]));
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<vT,vT> p = sincospi(a[i]);
      NT2_TEST_EQUAL(p.first,  nt2::sinpi(a[i]));
      NT2_TEST_EQUAL(p.second, nt2::cospi(a[i]));
    }
  }
}
