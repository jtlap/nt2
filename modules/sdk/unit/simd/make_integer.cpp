/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::make_integer SIMD"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/make_integer.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that make_integer on SIMD with unsigned target
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(make_uinteger_simd, NT2_SIMD_TYPES)
{
  using nt2::simd::native;
  using nt2::meta::make_integer;
  using boost::is_same;
  using boost::mpl::_;

  typedef NT2_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<typename make_integer<sizeof(T),unsigned>::type,ext_t> dst_t;

  NT2_TEST( (is_same< typename make_integer<sizeof(T),unsigned,native<_,ext_t> >::type
                    , dst_t
                    >::value
            )
          );
}

////////////////////////////////////////////////////////////////////////////////
// Test that make_integer on SIMD with signed target
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(make_integer_simd, NT2_SIMD_TYPES)
{
  using nt2::simd::native;
  using nt2::meta::make_integer;
  using boost::is_same;
  using boost::mpl::_;

  typedef NT2_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<typename make_integer<sizeof(T),signed>::type,ext_t> dst_t;

  NT2_TEST( (is_same< typename make_integer<sizeof(T),signed,native<_,ext_t> >::type
                    , dst_t
                    >::value
            )
          );
}
