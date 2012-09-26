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
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/simd/logical.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of true/false constant
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( true_false_integer_value, BOOST_SIMD_SIMD_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>                dst_t;

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::False<dst_t>())[i], nt2::logical<dst_t>(false) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::True<dst_t>())[i], nt2::logical<dst_t>(true) );
}
