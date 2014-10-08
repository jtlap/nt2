//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/value.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>


NT2_TEST_CASE_TPL(complex, BOOST_SIMD_REAL_TYPES)
{
  using std::complex;
  using nt2::value;
  using nt2::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(complex<T> const&)>::type
                  , complex<T> const&
                  );
  // specific values tests
  NT2_TEST_EQUAL(value(complex<T>(4,2)), complex<T>(4,2));
}

NT2_TEST_CASE_TPL(dry, BOOST_SIMD_REAL_TYPES)
{
  using nt2::dry;
  using nt2::value;
  using nt2::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(dry<T>)>::type
                  , T
                  );
  // specific values tests
  NT2_TEST_EQUAL(value(dry<T>(4)), T(4));
}
