/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::align_on"

#include <nt2/sdk/memory/align_on.hpp>
#include <nt2/sdk/memory/meta/align_on.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test the align_on version on integer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(align_on_int)
{
  using nt2::memory::align_on;

  NT2_TEST_EQUAL( align_on<0x01>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x02>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x04>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x08>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x10>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x20>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x40>(0x00), 0x00U );
  NT2_TEST_EQUAL( align_on<0x80>(0x00), 0x00U );

  NT2_TEST_EQUAL( align_on<0x02>(0x01), 0x02U );
  NT2_TEST_EQUAL( align_on<0x04>(0x03), 0x04U );
  NT2_TEST_EQUAL( align_on<0x08>(0x07), 0x08U );
  NT2_TEST_EQUAL( align_on<0x10>(0x0F), 0x10U );
  NT2_TEST_EQUAL( align_on<0x20>(0x1F), 0x20U );
  NT2_TEST_EQUAL( align_on<0x40>(0x3F), 0x40U );
  NT2_TEST_EQUAL( align_on<0x80>(0x7F), 0x80U );

  NT2_TEST_EQUAL( align_on<0x02>(0x02), 0x02U );
  NT2_TEST_EQUAL( align_on<0x04>(0x04), 0x04U );
  NT2_TEST_EQUAL( align_on<0x08>(0x08), 0x08U );
  NT2_TEST_EQUAL( align_on<0x10>(0x10), 0x10U );
  NT2_TEST_EQUAL( align_on<0x20>(0x20), 0x20U );
  NT2_TEST_EQUAL( align_on<0x40>(0x40), 0x40U );
  NT2_TEST_EQUAL( align_on<0x80>(0x80), 0x80U );
}

////////////////////////////////////////////////////////////////////////////////
// Test the align_on version on pointer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(align_on_ptr)
{
  using nt2::memory::align_on;

  void* null_  = reinterpret_cast<void*>(0);
  void* exact_ = reinterpret_cast<void*>(0xABCD8000);
  void* under_ = reinterpret_cast<void*>(0xABCD7FFF);

  NT2_TEST_EQUAL( align_on<0x01>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x02>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x04>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x08>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x10>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x20>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x40>(null_), null_ );
  NT2_TEST_EQUAL( align_on<0x80>(null_), null_ );

  NT2_TEST_EQUAL( align_on<0x02>(under_), exact_);
  NT2_TEST_EQUAL( align_on<0x04>(under_), exact_);
  NT2_TEST_EQUAL( align_on<0x08>(under_), exact_);
  NT2_TEST_EQUAL( align_on<0x10>(under_), exact_);
  NT2_TEST_EQUAL( align_on<0x20>(under_), exact_);
  NT2_TEST_EQUAL( align_on<0x40>(under_), exact_);
  NT2_TEST_EQUAL( align_on<0x80>(under_), exact_);

  NT2_TEST_EQUAL( align_on<0x02>(exact_), exact_);
  NT2_TEST_EQUAL( align_on<0x04>(exact_), exact_);
  NT2_TEST_EQUAL( align_on<0x08>(exact_), exact_);
  NT2_TEST_EQUAL( align_on<0x10>(exact_), exact_);
  NT2_TEST_EQUAL( align_on<0x20>(exact_), exact_);
  NT2_TEST_EQUAL( align_on<0x40>(exact_), exact_);
  NT2_TEST_EQUAL( align_on<0x80>(exact_), exact_);
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::align_on_c version
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(meta_align_on_c)
{
  using nt2::meta::align_on_c;

  NT2_TEST_EQUAL( (align_on_c<0x00,0x01>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x02>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x04>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x08>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x10>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x20>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x40>::value), 0x00U );
  NT2_TEST_EQUAL( (align_on_c<0x00,0x80>::value), 0x00U );

  NT2_TEST_EQUAL( (align_on_c<0x01,0x02>::value), 0x02U );
  NT2_TEST_EQUAL( (align_on_c<0x03,0x04>::value), 0x04U );
  NT2_TEST_EQUAL( (align_on_c<0x07,0x08>::value), 0x08U );
  NT2_TEST_EQUAL( (align_on_c<0x0F,0x10>::value), 0x10U );
  NT2_TEST_EQUAL( (align_on_c<0x1F,0x20>::value), 0x20U );
  NT2_TEST_EQUAL( (align_on_c<0x3F,0x40>::value), 0x40U );
  NT2_TEST_EQUAL( (align_on_c<0x7F,0x80>::value), 0x80U );

  NT2_TEST_EQUAL( (align_on_c<0x02,0x02>::value), 0x02U );
  NT2_TEST_EQUAL( (align_on_c<0x04,0x04>::value), 0x04U );
  NT2_TEST_EQUAL( (align_on_c<0x08,0x08>::value), 0x08U );
  NT2_TEST_EQUAL( (align_on_c<0x10,0x10>::value), 0x10U );
  NT2_TEST_EQUAL( (align_on_c<0x20,0x20>::value), 0x20U );
  NT2_TEST_EQUAL( (align_on_c<0x40,0x40>::value), 0x40U );
  NT2_TEST_EQUAL( (align_on_c<0x80,0x80>::value), 0x80U );
}

////////////////////////////////////////////////////////////////////////////////
// Test the meta::align_on version
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(meta_align_on)
{
  using nt2::meta::align_on;
  using boost::mpl::int_;

  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x01> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x02> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x04> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x08> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x10> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x20> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x40> >::value), 0x00 );
  NT2_TEST_EQUAL( (align_on<int_<0x00>,int_<0x80> >::value), 0x00 );

  NT2_TEST_EQUAL( (align_on<int_<0x01>,int_<0x02> >::value), 0x02 );
  NT2_TEST_EQUAL( (align_on<int_<0x03>,int_<0x04> >::value), 0x04 );
  NT2_TEST_EQUAL( (align_on<int_<0x07>,int_<0x08> >::value), 0x08 );
  NT2_TEST_EQUAL( (align_on<int_<0x0F>,int_<0x10> >::value), 0x10 );
  NT2_TEST_EQUAL( (align_on<int_<0x1F>,int_<0x20> >::value), 0x20 );
  NT2_TEST_EQUAL( (align_on<int_<0x3F>,int_<0x40> >::value), 0x40 );
  NT2_TEST_EQUAL( (align_on<int_<0x7F>,int_<0x80> >::value), 0x80 );

  NT2_TEST_EQUAL( (align_on<int_<0x02>,int_<0x02> >::value), 0x02 );
  NT2_TEST_EQUAL( (align_on<int_<0x04>,int_<0x04> >::value), 0x04 );
  NT2_TEST_EQUAL( (align_on<int_<0x08>,int_<0x08> >::value), 0x08 );
  NT2_TEST_EQUAL( (align_on<int_<0x10>,int_<0x10> >::value), 0x10 );
  NT2_TEST_EQUAL( (align_on<int_<0x20>,int_<0x20> >::value), 0x20 );
  NT2_TEST_EQUAL( (align_on<int_<0x40>,int_<0x40> >::value), 0x40 );
  NT2_TEST_EQUAL( (align_on<int_<0x80>,int_<0x80> >::value), 0x80 );
}
