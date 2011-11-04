/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::constants true/false"

#include <nt2/include/constants/true_false.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/simd/logical.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of true/false constant for integral types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( true_false_integer_value, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>                dst_t;
  typedef typename nt2::meta::as_unsigned<T>::type  uns_t;

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::False<dst_t>())[i], static_cast<T>(0) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::True<dst_t>())[i], nt2::logical<T>(~static_cast<uns_t>(0)) );
}

////////////////////////////////////////////////////////////////////////////////
// Test value of true/false constant for real types (which can't use ~0)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( true_false_real_value, BOOST_SIMD_SIMD_REAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>                dst_t;

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::False<dst_t>())[i], static_cast<T>(0) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::True<dst_t>())[i], nt2::logical<T>(nt2::Nan<T>()) );
}
