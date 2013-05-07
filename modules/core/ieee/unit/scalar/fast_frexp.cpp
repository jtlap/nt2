//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/fast_frexp.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( fast_frexp,  NT2_REAL_TYPES)
{
  using nt2::fast_frexp;
  using nt2::tag::fast_frexp_;

  typedef typename nt2::meta::as_integer<T,signed>::type iT;

  NT2_TEST_TYPE_IS( (typename nt2::meta::call<fast_frexp_(T)>::type)
                  , (std::pair<T,iT>)
                  );

  {
    iT e;
    T  m;

    fast_frexp(nt2::One<T>(), m, e);
    NT2_TEST_EQUAL(m, nt2::Half<T>());
    NT2_TEST_EQUAL(e, nt2::One<T>());
  }

  {
    iT e;
    T  m;

    m = fast_frexp(nt2::One<T>(), e);
    NT2_TEST_EQUAL(m, nt2::Half<T>());
    NT2_TEST_EQUAL(e, nt2::One<T>());
  }

  {
    iT e;
    T  m;

    boost::fusion::vector_tie(m,e) = fast_frexp(nt2::One<T>());
    NT2_TEST_EQUAL(m, nt2::Half<T>());
    NT2_TEST_EQUAL(e, nt2::One<T>());
  }

  {
    std::pair<T,typename nt2::meta::as_integer<T,signed>::type> p;

    p = fast_frexp(nt2::One<T>());
    NT2_TEST_EQUAL(p.first  , nt2::Half<T>());
    NT2_TEST_EQUAL(p.second , nt2::One<T>());
  }
}
