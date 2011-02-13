/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::category_of simd"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test category of SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(simd_category)
{
  using nt2::simd::native;
  using nt2::meta::hierarchy_of;
  using boost::is_same;
  using namespace nt2;

/*
  typedef NT2_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef functors::simd_<tag::arithmetic_,ext_t,1> cat_t;

  #if defined(NT2_SIMD_SSE_FAMILY)
  NT2_TEST((is_same<category_of<native<double       ,ext_t> >::type, cat_t>::value));
  NT2_TEST((is_same<category_of<native<nt2::uint64_t,ext_t> >::type, cat_t>::value));
  NT2_TEST((is_same<category_of<native<nt2::int64_t,ext_t > >::type, cat_t>::value));
  #endif

  NT2_TEST((is_same<category_of<native<float    ,ext_t> >::type , cat_t >::value));
  NT2_TEST((is_same<category_of<native<nt2::uint32_t ,ext_t> >::type , cat_t >::value));
  NT2_TEST((is_same<category_of<native<nt2::uint16_t ,ext_t> >::type , cat_t >::value));
  NT2_TEST((is_same<category_of<native<nt2::uint8_t  ,ext_t> >::type , cat_t >::value));
  NT2_TEST((is_same<category_of<native<nt2::int32_t  ,ext_t> >::type , cat_t >::value));
  NT2_TEST((is_same<category_of<native<nt2::int16_t  ,ext_t> >::type , cat_t >::value));
  NT2_TEST((is_same<category_of<native<nt2::int8_t   ,ext_t> >::type , cat_t >::value));
*/
}
