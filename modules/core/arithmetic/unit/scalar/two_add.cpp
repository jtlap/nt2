//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/arithmetic/include/functions/two_add.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( two_add, NT2_REAL_TYPES)
{
  using nt2::two_add;
  using nt2::tag::two_add_;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<two_add_(T,T)>::type)
                  , (std::pair<T,T>)
                  );

  T inf_    = nt2::Inf<T>();
  T zero_   = nt2::Zero<T>();
  T one_    = nt2::One<T>();
  T half_   = nt2::Half<T>();
  T eps_    = nt2::Eps<T>();
  T eps_2_  = eps_/T(2);

  {
    T s,r;

    two_add(inf_,zero_, s, r);
    NT2_TEST_EQUAL(s, inf_);
    NT2_TEST_EQUAL(r, zero_);

    two_add(zero_, inf_, s, r);
    NT2_TEST_EQUAL(s, inf_);
    NT2_TEST_EQUAL(r, zero_);

    two_add(half_+ eps_2_, half_, s, r);
    NT2_TEST_EQUAL(s, one_);
    NT2_TEST_EQUAL(r, eps_2_);

    two_add(half_, half_+ eps_2_, s, r);
    NT2_TEST_EQUAL(s, one_);
    NT2_TEST_EQUAL(r, eps_2_);
  }

  {
    T s,r;

    s = two_add(inf_,zero_, r);
    NT2_TEST_EQUAL(s, inf_);
    NT2_TEST_EQUAL(r, zero_);

    s = two_add(zero_, inf_, r);
    NT2_TEST_EQUAL(s, inf_);
    NT2_TEST_EQUAL(r, zero_);

    s = two_add(half_+ eps_2_, half_, r);
    NT2_TEST_EQUAL(s, one_);
    NT2_TEST_EQUAL(r, eps_2_);

    s = two_add(half_, half_+ eps_2_, r);
    NT2_TEST_EQUAL(s, one_);
    NT2_TEST_EQUAL(r, eps_2_);
  }

  {
    T s,r;

    boost::fusion::vector_tie(s,r) = two_add(inf_,zero_);
    NT2_TEST_EQUAL(s, inf_);
    NT2_TEST_EQUAL(r, zero_);

    boost::fusion::vector_tie(s,r) = two_add(zero_, inf_);
    NT2_TEST_EQUAL(s, inf_);
    NT2_TEST_EQUAL(r, zero_);

    boost::fusion::vector_tie(s,r) = two_add(half_+ eps_2_, half_);
    NT2_TEST_EQUAL(s, one_);
    NT2_TEST_EQUAL(r, eps_2_);

    boost::fusion::vector_tie(s,r) = two_add(half_, half_+ eps_2_);
    NT2_TEST_EQUAL(s, one_);
    NT2_TEST_EQUAL(r, eps_2_);
  }

  {
    std::pair<T,T> p;

    p = two_add(inf_,zero_);
    NT2_TEST_EQUAL(p.first, inf_);
    NT2_TEST_EQUAL(p.second, zero_);

    p = two_add(zero_, inf_);
    NT2_TEST_EQUAL(p.first, inf_);
    NT2_TEST_EQUAL(p.second, zero_);

    p = two_add(half_+ eps_2_, half_);
    NT2_TEST_EQUAL(p.first, one_);
    NT2_TEST_EQUAL(p.second, eps_2_);

    p = two_add(half_, half_+ eps_2_);
    NT2_TEST_EQUAL(p.first, one_);
    NT2_TEST_EQUAL(p.second, eps_2_);
  }
}
