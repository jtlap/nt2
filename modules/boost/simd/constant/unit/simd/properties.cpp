/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 constants simd properties"

#include <boost/simd/include/constants/properties.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
   
#ifdef BOOST_MSVC
  #pragma warning(disable: 4146) // unary minus applied to unsigned
#endif

////////////////////////////////////////////////////////////////////////////////
// Test values for sigmask
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(signmask, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
    NT2_TEST_EQUAL( (boost::simd::Signmask<vd_t>())[i], boost::simd::Signmask<T>() );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmax
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(valmax, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
    NT2_TEST_EQUAL( (boost::simd::Valmax<vd_t>())[i], boost::simd::Valmax<T>() );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmin
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(valmin, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
    NT2_TEST_EQUAL( (boost::simd::Valmin<vd_t>())[i], boost::simd::Valmin<T>() );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for maxleftshift
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(Maxleftshift, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
    NT2_TEST_EQUAL( (boost::simd::Maxleftshift<vd_t>())[i], boost::simd::Maxleftshift<T>() );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for IEEE specs
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(ieee, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
  {
    NT2_TEST_EQUAL( (boost::simd::Nbmantissabits<vd_t>())[i], boost::simd::Nbmantissabits<T>() );
    NT2_TEST_EQUAL( (boost::simd::Nbexponentbits<vd_t>())[i], boost::simd::Nbexponentbits<T>() );
    NT2_TEST_EQUAL( (boost::simd::Maxexponent<vd_t>())[i], boost::simd::Maxexponent<T>() );
    NT2_TEST_EQUAL( (boost::simd::Minexponent<vd_t>())[i], boost::simd::Minexponent<T>() );
    NT2_TEST_EQUAL( (boost::simd::Ldexpmask<vd_t>())[i], boost::simd::Ldexpmask<T>() );
    NT2_TEST_EQUAL( (boost::simd::Nbdigits<vd_t>())[i], boost::simd::Nbdigits<T>() );
  }
}
