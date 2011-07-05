/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::memory::is_aligned"

#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/meta/is_aligned.hpp>

#include <boost/mpl/int.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test the defautlt is_aligned version on integer
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_aligned_int_default)
{
  using boost::simd::memory::is_aligned;

  BOOST_SIMD_TEST( is_aligned(0x00)                    );
  BOOST_SIMD_TEST( !is_aligned(BOOST_SIMD_CONFIG_ALIGNMENT-1) );
  BOOST_SIMD_TEST( is_aligned(BOOST_SIMD_CONFIG_ALIGNMENT*4)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on integer/integer
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_aligned_int)
{
  using boost::simd::memory::is_aligned;

  BOOST_SIMD_TEST( is_aligned(0x00,0x01) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x02) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x04) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x08) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x10) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x20) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x40) );
  BOOST_SIMD_TEST( is_aligned(0x00,0x80) );

  BOOST_SIMD_TEST( !is_aligned(0x01,0x02) );
  BOOST_SIMD_TEST( !is_aligned(0x03,0x04) );
  BOOST_SIMD_TEST( !is_aligned(0x07,0x08) );
  BOOST_SIMD_TEST( !is_aligned(0x0F,0x10) );
  BOOST_SIMD_TEST( !is_aligned(0x1F,0x20) );
  BOOST_SIMD_TEST( !is_aligned(0x3F,0x40) );
  BOOST_SIMD_TEST( !is_aligned(0x7F,0x80) );

  BOOST_SIMD_TEST( is_aligned(0x02,0x02) );
  BOOST_SIMD_TEST( is_aligned(0x04,0x04) );
  BOOST_SIMD_TEST( is_aligned(0x08,0x08) );
  BOOST_SIMD_TEST( is_aligned(0x10,0x10) );
  BOOST_SIMD_TEST( is_aligned(0x20,0x20) );
  BOOST_SIMD_TEST( is_aligned(0x40,0x40) );
  BOOST_SIMD_TEST( is_aligned(0x80,0x80) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on integer/meta
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_aligned_int_meta_int)
{
  using boost::simd::memory::is_aligned;

  BOOST_SIMD_TEST( is_aligned<0x01>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x02>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x04>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x08>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x10>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x20>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x40>(0x00) );
  BOOST_SIMD_TEST( is_aligned<0x80>(0x00) );

  BOOST_SIMD_TEST( !is_aligned<0x02>(0x01) );
  BOOST_SIMD_TEST( !is_aligned<0x04>(0x03) );
  BOOST_SIMD_TEST( !is_aligned<0x08>(0x07) );
  BOOST_SIMD_TEST( !is_aligned<0x10>(0x0F) );
  BOOST_SIMD_TEST( !is_aligned<0x20>(0x1F) );
  BOOST_SIMD_TEST( !is_aligned<0x40>(0x33) );
  BOOST_SIMD_TEST( !is_aligned<0x80>(0x7C) );

  BOOST_SIMD_TEST( is_aligned<0x02>(0x02) );
  BOOST_SIMD_TEST( is_aligned<0x04>(0x04) );
  BOOST_SIMD_TEST( is_aligned<0x08>(0x08) );
  BOOST_SIMD_TEST( is_aligned<0x10>(0x10) );
  BOOST_SIMD_TEST( is_aligned<0x20>(0x20) );
  BOOST_SIMD_TEST( is_aligned<0x40>(0x40) );
  BOOST_SIMD_TEST( is_aligned<0x80>(0x80) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on pointer
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_aligned_ptr)
{
  using boost::simd::memory::is_aligned;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD8000);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  BOOST_SIMD_TEST( is_aligned(null_,0x01) );
  BOOST_SIMD_TEST( is_aligned(null_,0x02) );
  BOOST_SIMD_TEST( is_aligned(null_,0x04) );
  BOOST_SIMD_TEST( is_aligned(null_,0x08) );
  BOOST_SIMD_TEST( is_aligned(null_,0x10) );
  BOOST_SIMD_TEST( is_aligned(null_,0x20) );
  BOOST_SIMD_TEST( is_aligned(null_,0x40) );
  BOOST_SIMD_TEST( is_aligned(null_,0x80) );

  BOOST_SIMD_TEST( !is_aligned(under_,0x02) );
  BOOST_SIMD_TEST( !is_aligned(under_,0x04) );
  BOOST_SIMD_TEST( !is_aligned(under_,0x08) );
  BOOST_SIMD_TEST( !is_aligned(under_,0x10) );
  BOOST_SIMD_TEST( !is_aligned(under_,0x20) );
  BOOST_SIMD_TEST( !is_aligned(under_,0x40) );
  BOOST_SIMD_TEST( !is_aligned(under_,0x80) );

  BOOST_SIMD_TEST( is_aligned(exact_,0x02) );
  BOOST_SIMD_TEST( is_aligned(exact_,0x04) );
  BOOST_SIMD_TEST( is_aligned(exact_,0x08) );
  BOOST_SIMD_TEST( is_aligned(exact_,0x10) );
  BOOST_SIMD_TEST( is_aligned(exact_,0x20) );
  BOOST_SIMD_TEST( is_aligned(exact_,0x40) );
  BOOST_SIMD_TEST( is_aligned(exact_,0x80) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on pointer/meta int
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_aligned_ptr_meta)
{
  using boost::simd::memory::is_aligned;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD8000);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  BOOST_SIMD_TEST( is_aligned<0x01>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x02>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x04>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x08>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x10>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x20>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x40>(null_) );
  BOOST_SIMD_TEST( is_aligned<0x80>(null_) );

  BOOST_SIMD_TEST( !is_aligned<0x02>(under_) );
  BOOST_SIMD_TEST( !is_aligned<0x04>(under_) );
  BOOST_SIMD_TEST( !is_aligned<0x08>(under_) );
  BOOST_SIMD_TEST( !is_aligned<0x10>(under_) );
  BOOST_SIMD_TEST( !is_aligned<0x20>(under_) );
  BOOST_SIMD_TEST( !is_aligned<0x40>(under_) );
  BOOST_SIMD_TEST( !is_aligned<0x80>(under_) );

  BOOST_SIMD_TEST( is_aligned<0x02>(exact_) );
  BOOST_SIMD_TEST( is_aligned<0x04>(exact_) );
  BOOST_SIMD_TEST( is_aligned<0x08>(exact_) );
  BOOST_SIMD_TEST( is_aligned<0x10>(exact_) );
  BOOST_SIMD_TEST( is_aligned<0x20>(exact_) );
  BOOST_SIMD_TEST( is_aligned<0x40>(exact_) );
  BOOST_SIMD_TEST( is_aligned<0x80>(exact_) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned default version on pointer
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(is_aligned_ptr_default)
{
  using boost::simd::memory::is_aligned;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD * BOOST_SIMD_CONFIG_ALIGNMENT);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  BOOST_SIMD_TEST( is_aligned(null_) );
  BOOST_SIMD_TEST( !is_aligned(under_) );
  BOOST_SIMD_TEST( is_aligned(exact_) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_aligned_c version
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(meta_is_aligned_c)
{
  using boost::simd::meta::is_aligned_c;

  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x01>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x02>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x04>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x08>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x10>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x20>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x40>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x00,0x80>::value) );

  BOOST_SIMD_TEST( !(is_aligned_c<0x01,0x02>::value) );
  BOOST_SIMD_TEST( !(is_aligned_c<0x03,0x04>::value) );
  BOOST_SIMD_TEST( !(is_aligned_c<0x07,0x08>::value) );
  BOOST_SIMD_TEST( !(is_aligned_c<0x0F,0x10>::value) );
  BOOST_SIMD_TEST( !(is_aligned_c<0x1F,0x20>::value) );
  BOOST_SIMD_TEST( !(is_aligned_c<0x33,0x40>::value) );
  BOOST_SIMD_TEST( !(is_aligned_c<0x6F,0x80>::value) );

  BOOST_SIMD_TEST( (is_aligned_c<0x01,0x01>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x02,0x02>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x04,0x04>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x08,0x08>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x10,0x10>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x20,0x20>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x40,0x40>::value) );
  BOOST_SIMD_TEST( (is_aligned_c<0x80,0x80>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_aligned version
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(meta_is_aligned)
{
  using boost::simd::meta::is_aligned;
  using boost::mpl::int_;

  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x01> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x02> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x04> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x08> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x10> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x20> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x40> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x00>,int_<0x80> >::value) );

  BOOST_SIMD_TEST( !(is_aligned<int_<0x01>,int_<0x02> >::value) );
  BOOST_SIMD_TEST( !(is_aligned<int_<0x03>,int_<0x04> >::value) );
  BOOST_SIMD_TEST( !(is_aligned<int_<0x07>,int_<0x08> >::value) );
  BOOST_SIMD_TEST( !(is_aligned<int_<0x0F>,int_<0x10> >::value) );
  BOOST_SIMD_TEST( !(is_aligned<int_<0x1F>,int_<0x20> >::value) );
  BOOST_SIMD_TEST( !(is_aligned<int_<0x33>,int_<0x40> >::value) );
  BOOST_SIMD_TEST( !(is_aligned<int_<0x6F>,int_<0x80> >::value) );

  BOOST_SIMD_TEST( (is_aligned<int_<0x01>,int_<0x01> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x02>,int_<0x02> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x04>,int_<0x04> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x08>,int_<0x08> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x10>,int_<0x10> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x20>,int_<0x20> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x40>,int_<0x40> >::value) );
  BOOST_SIMD_TEST( (is_aligned<int_<0x80>,int_<0x80> >::value) );
}
