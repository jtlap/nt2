/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::as_unsigned SIMD"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_unsigned is correct
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_unsigned, NT2_SIMD_TYPES)
{
	using nt2::simd::native;
  using nt2::meta::as_unsigned;
  using boost::is_same;
  using boost::mpl::_;

  typedef NT2_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<typename as_unsigned<T>::type,ext_t> dst_t;

  NT2_TEST( (is_same< typename as_unsigned< native<T,ext_t> >::type, dst_t>::value	));
}
