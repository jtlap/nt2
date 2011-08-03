/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::scalar_of SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on SIMD
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(scalar_of_simd, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::scalar_of;
  using boost::is_same;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 native_t;

  NT2_TEST( (is_same<typename scalar_of<native_t>::type, T >::value) );
}
