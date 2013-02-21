//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/ieee/include/functions/modf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/frac.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( modf, BOOST_SIMD_TYPES)
{
  using nt2::modf;
  using nt2::tag::modf_;

  NT2_TEST_TYPE_IS( (typename nt2::meta::call<modf_(T)>::type)
                  , (std::pair<T,T>)
                  );

  {
    T e;
    T m;

    modf(T(1.5), m, e);
    NT2_TEST_EQUAL(m, nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(e, T(.5));
  }

  {
    T e;
    T m;

    m = modf(T(1.5), e);
    NT2_TEST_EQUAL(m, nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(e, T(.5));
  }

  {
    T e;
    T m;

    boost::fusion::vector_tie(m,e) = modf(T(1.5));
    NT2_TEST_EQUAL(m, nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(e, T(.5));
  }

  {
    std::pair<T,T> p;

    p = modf(T(1.5));
    NT2_TEST_EQUAL(p.first  , nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(p.second , T(.5));
  }
}
