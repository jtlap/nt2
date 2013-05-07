//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/two_add.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( two_add, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::two_add;
  using boost::simd::tag::two_add_;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<two_add_(T,T)>::type)
                  , (std::pair<T,T>)
                  );

  T inf_    = boost::simd::Inf<T>();
  T zero_   = boost::simd::Zero<T>();
  T one_    = boost::simd::One<T>();
  T half_   = boost::simd::Half<T>();
  T eps_    = boost::simd::Eps<T>();
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
