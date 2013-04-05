//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/trigonometric/include/functions/fast_sincosd.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/fast_sind.hpp>
#include <nt2/include/functions/fast_cosd.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( fast_sincosd_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::fast_sincosd;
  using nt2::tag::fast_sincosd_;
  T a[] = {nt2::Zero<T>(), nt2::One<T>(), T(120), T(180),
           T(90), nt2::Inf<T>(), nt2::Minf<T>(), nt2::Nan<T>()};
  size_t N =  sizeof(a)/sizeof(T);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<fast_sincosd_(T)>::type)
                  , (std::pair<T,T>)
                  );

  {
    T s, c;
    for(size_t i=0; i < N; ++i)
    {
      fast_sincosd(a[i], s, c);
      NT2_TEST_EQUAL(s, nt2::fast_sind(a[i]));
      NT2_TEST_EQUAL(c, nt2::fast_cosd(a[i]));
    }
  }

  {
    T s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = fast_sincosd(a[i], c);
      NT2_TEST_EQUAL(s, nt2::fast_sind(a[i]));
      NT2_TEST_EQUAL(c, nt2::fast_cosd(a[i]));
    }
  }

  {
    T s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = fast_sincosd(a[i]);
      NT2_TEST_EQUAL(s, nt2::fast_sind(a[i]));
      NT2_TEST_EQUAL(c, nt2::fast_cosd(a[i]));
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<T,T> p = fast_sincosd(a[i]);
      NT2_TEST_EQUAL(p.first,  nt2::fast_sind(a[i]));
      NT2_TEST_EQUAL(p.second, nt2::fast_cosd(a[i]));
    }
  }

}
