/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::memory::is_aligned"

#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/meta/is_aligned.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test the defautlt is_aligned version on integer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_aligned_int_default)
{
  using boost::simd::memory::is_aligned;

  NT2_TEST( is_aligned(0x00)                    );
  NT2_TEST( !is_aligned(BOOST_SIMD_CONFIG_ALIGNMENT-1) );
  NT2_TEST( is_aligned(BOOST_SIMD_CONFIG_ALIGNMENT*4)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on integer/integer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_aligned_int)
{
  using boost::simd::memory::is_aligned;

  NT2_TEST( is_aligned(0x00,0x01) );
  NT2_TEST( is_aligned(0x00,0x02) );
  NT2_TEST( is_aligned(0x00,0x04) );
  NT2_TEST( is_aligned(0x00,0x08) );
  NT2_TEST( is_aligned(0x00,0x10) );
  NT2_TEST( is_aligned(0x00,0x20) );
  NT2_TEST( is_aligned(0x00,0x40) );
  NT2_TEST( is_aligned(0x00,0x80) );

  NT2_TEST( !is_aligned(0x01,0x02) );
  NT2_TEST( !is_aligned(0x03,0x04) );
  NT2_TEST( !is_aligned(0x07,0x08) );
  NT2_TEST( !is_aligned(0x0F,0x10) );
  NT2_TEST( !is_aligned(0x1F,0x20) );
  NT2_TEST( !is_aligned(0x3F,0x40) );
  NT2_TEST( !is_aligned(0x7F,0x80) );

  NT2_TEST( is_aligned(0x02,0x02) );
  NT2_TEST( is_aligned(0x04,0x04) );
  NT2_TEST( is_aligned(0x08,0x08) );
  NT2_TEST( is_aligned(0x10,0x10) );
  NT2_TEST( is_aligned(0x20,0x20) );
  NT2_TEST( is_aligned(0x40,0x40) );
  NT2_TEST( is_aligned(0x80,0x80) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on integer/meta
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_aligned_int_meta_int)
{
  using boost::simd::memory::is_aligned;

  NT2_TEST( is_aligned<0x01>(0x00) );
  NT2_TEST( is_aligned<0x02>(0x00) );
  NT2_TEST( is_aligned<0x04>(0x00) );
  NT2_TEST( is_aligned<0x08>(0x00) );
  NT2_TEST( is_aligned<0x10>(0x00) );
  NT2_TEST( is_aligned<0x20>(0x00) );
  NT2_TEST( is_aligned<0x40>(0x00) );
  NT2_TEST( is_aligned<0x80>(0x00) );

  NT2_TEST( !is_aligned<0x02>(0x01) );
  NT2_TEST( !is_aligned<0x04>(0x03) );
  NT2_TEST( !is_aligned<0x08>(0x07) );
  NT2_TEST( !is_aligned<0x10>(0x0F) );
  NT2_TEST( !is_aligned<0x20>(0x1F) );
  NT2_TEST( !is_aligned<0x40>(0x33) );
  NT2_TEST( !is_aligned<0x80>(0x7C) );

  NT2_TEST( is_aligned<0x02>(0x02) );
  NT2_TEST( is_aligned<0x04>(0x04) );
  NT2_TEST( is_aligned<0x08>(0x08) );
  NT2_TEST( is_aligned<0x10>(0x10) );
  NT2_TEST( is_aligned<0x20>(0x20) );
  NT2_TEST( is_aligned<0x40>(0x40) );
  NT2_TEST( is_aligned<0x80>(0x80) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on pointer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_aligned_ptr)
{
  using boost::simd::memory::is_aligned;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD8000);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  NT2_TEST( is_aligned(null_,0x01) );
  NT2_TEST( is_aligned(null_,0x02) );
  NT2_TEST( is_aligned(null_,0x04) );
  NT2_TEST( is_aligned(null_,0x08) );
  NT2_TEST( is_aligned(null_,0x10) );
  NT2_TEST( is_aligned(null_,0x20) );
  NT2_TEST( is_aligned(null_,0x40) );
  NT2_TEST( is_aligned(null_,0x80) );

  NT2_TEST( !is_aligned(under_,0x02) );
  NT2_TEST( !is_aligned(under_,0x04) );
  NT2_TEST( !is_aligned(under_,0x08) );
  NT2_TEST( !is_aligned(under_,0x10) );
  NT2_TEST( !is_aligned(under_,0x20) );
  NT2_TEST( !is_aligned(under_,0x40) );
  NT2_TEST( !is_aligned(under_,0x80) );

  NT2_TEST( is_aligned(exact_,0x02) );
  NT2_TEST( is_aligned(exact_,0x04) );
  NT2_TEST( is_aligned(exact_,0x08) );
  NT2_TEST( is_aligned(exact_,0x10) );
  NT2_TEST( is_aligned(exact_,0x20) );
  NT2_TEST( is_aligned(exact_,0x40) );
  NT2_TEST( is_aligned(exact_,0x80) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned version on pointer/meta int
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_aligned_ptr_meta)
{
  using boost::simd::memory::is_aligned;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD8000);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  NT2_TEST( is_aligned<0x01>(null_) );
  NT2_TEST( is_aligned<0x02>(null_) );
  NT2_TEST( is_aligned<0x04>(null_) );
  NT2_TEST( is_aligned<0x08>(null_) );
  NT2_TEST( is_aligned<0x10>(null_) );
  NT2_TEST( is_aligned<0x20>(null_) );
  NT2_TEST( is_aligned<0x40>(null_) );
  NT2_TEST( is_aligned<0x80>(null_) );

  NT2_TEST( !is_aligned<0x02>(under_) );
  NT2_TEST( !is_aligned<0x04>(under_) );
  NT2_TEST( !is_aligned<0x08>(under_) );
  NT2_TEST( !is_aligned<0x10>(under_) );
  NT2_TEST( !is_aligned<0x20>(under_) );
  NT2_TEST( !is_aligned<0x40>(under_) );
  NT2_TEST( !is_aligned<0x80>(under_) );

  NT2_TEST( is_aligned<0x02>(exact_) );
  NT2_TEST( is_aligned<0x04>(exact_) );
  NT2_TEST( is_aligned<0x08>(exact_) );
  NT2_TEST( is_aligned<0x10>(exact_) );
  NT2_TEST( is_aligned<0x20>(exact_) );
  NT2_TEST( is_aligned<0x40>(exact_) );
  NT2_TEST( is_aligned<0x80>(exact_) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the is_aligned default version on pointer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_aligned_ptr_default)
{
  using boost::simd::memory::is_aligned;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD * BOOST_SIMD_CONFIG_ALIGNMENT);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  NT2_TEST( is_aligned(null_) );
  NT2_TEST( !is_aligned(under_) );
  NT2_TEST( is_aligned(exact_) );
}

#if defined(_MSC_VER) || defined(__GNUC__)
NT2_TEST_CASE(is_aligned_restrict)
{
  using boost::simd::memory::is_aligned;

  int * __restrict p = 0;
  NT2_TEST( is_aligned(p) );
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_aligned_c version
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(meta_is_aligned_c)
{
  using boost::simd::meta::is_aligned_c;

  NT2_TEST( (is_aligned_c<0x00,0x01>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x02>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x04>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x08>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x10>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x20>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x40>::value) );
  NT2_TEST( (is_aligned_c<0x00,0x80>::value) );

  NT2_TEST( !(is_aligned_c<0x01,0x02>::value) );
  NT2_TEST( !(is_aligned_c<0x03,0x04>::value) );
  NT2_TEST( !(is_aligned_c<0x07,0x08>::value) );
  NT2_TEST( !(is_aligned_c<0x0F,0x10>::value) );
  NT2_TEST( !(is_aligned_c<0x1F,0x20>::value) );
  NT2_TEST( !(is_aligned_c<0x33,0x40>::value) );
  NT2_TEST( !(is_aligned_c<0x6F,0x80>::value) );

  NT2_TEST( (is_aligned_c<0x01,0x01>::value) );
  NT2_TEST( (is_aligned_c<0x02,0x02>::value) );
  NT2_TEST( (is_aligned_c<0x04,0x04>::value) );
  NT2_TEST( (is_aligned_c<0x08,0x08>::value) );
  NT2_TEST( (is_aligned_c<0x10,0x10>::value) );
  NT2_TEST( (is_aligned_c<0x20,0x20>::value) );
  NT2_TEST( (is_aligned_c<0x40,0x40>::value) );
  NT2_TEST( (is_aligned_c<0x80,0x80>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::is_aligned version
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(meta_is_aligned)
{
  using boost::simd::meta::is_aligned;
  using boost::mpl::int_;

  NT2_TEST( (is_aligned<int_<0x00>,int_<0x01> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x02> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x04> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x08> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x10> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x20> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x40> >::value) );
  NT2_TEST( (is_aligned<int_<0x00>,int_<0x80> >::value) );

  NT2_TEST( !(is_aligned<int_<0x01>,int_<0x02> >::value) );
  NT2_TEST( !(is_aligned<int_<0x03>,int_<0x04> >::value) );
  NT2_TEST( !(is_aligned<int_<0x07>,int_<0x08> >::value) );
  NT2_TEST( !(is_aligned<int_<0x0F>,int_<0x10> >::value) );
  NT2_TEST( !(is_aligned<int_<0x1F>,int_<0x20> >::value) );
  NT2_TEST( !(is_aligned<int_<0x33>,int_<0x40> >::value) );
  NT2_TEST( !(is_aligned<int_<0x6F>,int_<0x80> >::value) );

  NT2_TEST( (is_aligned<int_<0x01>,int_<0x01> >::value) );
  NT2_TEST( (is_aligned<int_<0x02>,int_<0x02> >::value) );
  NT2_TEST( (is_aligned<int_<0x04>,int_<0x04> >::value) );
  NT2_TEST( (is_aligned<int_<0x08>,int_<0x08> >::value) );
  NT2_TEST( (is_aligned<int_<0x10>,int_<0x10> >::value) );
  NT2_TEST( (is_aligned<int_<0x20>,int_<0x20> >::value) );
  NT2_TEST( (is_aligned<int_<0x40>,int_<0x40> >::value) );
  NT2_TEST( (is_aligned<int_<0x80>,int_<0x80> >::value) );
}
