//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/toolbox/ieee/include/functions/modf.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/functions/frac.hpp>
#include <boost/simd/include/functions/trunc.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( modf, BOOST_SIMD_TYPES)
{
  using boost::simd::modf;
  using boost::simd::tag::modf_;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<modf_(T)>::type)
                  , (std::pair<T,T>)
                  );

  {
    T e;
    T m;

    modf(T(1.5), m, e);
    NT2_TEST_EQUAL(m, boost::simd::trunc(T(1.5)));
    NT2_TEST_EQUAL(e, T(.5));
  }

  {
    T e;
    T m;

    m = modf(T(1.5), e);
    NT2_TEST_EQUAL(m, boost::simd::trunc(T(1.5)));
    NT2_TEST_EQUAL(e, T(.5));
  }

  {
    T e;
    T m;

    boost::fusion::vector_tie(m,e) = modf(T(1.5));
    NT2_TEST_EQUAL(m, boost::simd::trunc(T(1.5)));
    NT2_TEST_EQUAL(e, T(.5));
  }

  {
    std::pair<T,T> p;

    p = modf(T(1.5));
    NT2_TEST_EQUAL(p.first  , boost::simd::trunc(T(1.5)));
    NT2_TEST_EQUAL(p.second , T(.5));
  }
}
