//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/modf.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( modf, NT2_TYPES)
{
  using nt2::modf;
  using nt2::tag::modf_;

  NT2_TEST_TYPE_IS( (typename nt2::meta::call<modf_(T)>::type)
                  , (std::pair<T,T>)
                  );

  {
    T ent;
    T frac;

    modf(T(1.5), frac, ent);
    NT2_TEST_EQUAL(ent, nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(frac , T(.5));
  }

  {
    T ent;
    T frac;

    frac = modf(T(1.5), ent);
    NT2_TEST_EQUAL(ent, nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(frac , T(.5));
  }

  {
    T ent;
    T frac;

    boost::fusion::vector_tie(frac,ent) = modf(T(1.5));
    NT2_TEST_EQUAL(ent, nt2::trunc(T(1.5)));
    NT2_TEST_EQUAL(frac , T(.5));
  }

  {
    std::pair<T,T> p;

    p = modf(T(1.5));
    NT2_TEST_EQUAL(p.first  , T(.5));
    NT2_TEST_EQUAL(p.second , nt2::trunc(T(1.5)));
  }
}
