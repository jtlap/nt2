/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::value"

#include <boost/mpl/integral_c.hpp>
#include <boost/simd/include/functions/value.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/config/type_lists.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/splat.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(simd, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::splat;
  using boost::simd::value;
  using boost::simd::tag::value_;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> native_t;
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(native_t&)>::type
                  , native_t&
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(native_t const&)>::type
                  , native_t const&
                  );

  NT2_TEST_EQUAL(value(splat<native_t>(42)), splat<native_t>(42));
}

NT2_TEST_CASE_TPL(logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::splat;
  using boost::simd::value;
  using boost::simd::tag::value_;

  typedef native<logical<T>,BOOST_SIMD_DEFAULT_EXTENSION> native_t;
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(native_t const&)>::type
                  , native_t const&
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(native_t&)>::type
                  , native_t&
                  );

  NT2_TEST_EQUAL(value(splat<native_t>(true)), splat<native_t>(true));
}
