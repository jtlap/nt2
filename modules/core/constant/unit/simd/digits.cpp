//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::constants digits"

#include <nt2/include/constants/digits.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4309) // truncation of constant value
#endif

////////////////////////////////////////////////////////////////////////////////
// Test value of digit constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( digit_value, BOOST_SIMD_SIMD_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>             dst_t;

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mten<dst_t>())[i], static_cast<T>(  -10 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mnine<dst_t>())[i], static_cast<T>( -9 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Meight<dst_t>())[i], static_cast<T>( -8 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mseven<dst_t>())[i], static_cast<T>( -7 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Msix<dst_t>())[i], static_cast<T>( -6 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mfive<dst_t>())[i], static_cast<T>( -5 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mfour<dst_t>())[i], static_cast<T>( -4 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mthree<dst_t>())[i], static_cast<T>( -3 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mtwo<dst_t>())[i], static_cast<T>( -2 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Mone<dst_t>())[i], static_cast<T>( -1 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Zero<dst_t>())[i], static_cast<T>(  0 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Ten<dst_t>())[i], static_cast<T>(  10 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Nine<dst_t>())[i], static_cast<T>( 9 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Eight<dst_t>())[i], static_cast<T>( 8 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Seven<dst_t>())[i], static_cast<T>( 7 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Six<dst_t>())[i], static_cast<T>( 6 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Five<dst_t>())[i], static_cast<T>( 5 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Four<dst_t>())[i], static_cast<T>( 4 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Three<dst_t>())[i], static_cast<T>( 3 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::Two<dst_t>())[i], static_cast<T>( 2 ) );

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::One<dst_t>())[i], static_cast<T>( 1 ) );
}

////////////////////////////////////////////////////////////////////////////////
// Test integral_constant for every base types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( integral_constant, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>             dst_t;

  for(std::size_t i=0; i< nt2::meta::cardinal_of<dst_t>::value;++i)
    NT2_TEST_EQUAL( (nt2::integral_constant<dst_t,42>())[i], static_cast<T>(42) );
}
