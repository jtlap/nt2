/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::constants eps related"

#include <boost/simd/include/constants/eps_related.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/simd/sdk/simd/native.hpp>
   
////////////////////////////////////////////////////////////////////////////////
// Test values for IEEE specs
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(eps, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t> vd_t;
  for(std::size_t i=0; i< boost::simd::meta::cardinal_of<vd_t>::value;++i)
  {
    NT2_TEST_EQUAL( (boost::simd::Eps<vd_t>())[i], boost::simd::Eps<T>() );
    NT2_TEST_EQUAL( (boost::simd::Halfeps<vd_t>())[i], boost::simd::Halfeps<T>() );
    NT2_TEST_EQUAL( (boost::simd::Threeeps<vd_t>())[i], boost::simd::Threeeps<T>() );
    NT2_TEST_EQUAL( (boost::simd::Sqrteps<vd_t>())[i], boost::simd::Sqrteps<T>() );
    NT2_TEST_EQUAL( (boost::simd::Fourthrooteps<vd_t>())[i], boost::simd::Fourthrooteps<T>() );
    NT2_TEST_EQUAL( (boost::simd::Thirdrooteps<vd_t>())[i], boost::simd::Thirdrooteps<T>() );
    NT2_TEST_EQUAL( (boost::simd::Mlogeps2<vd_t>())[i], boost::simd::Mlogeps2<T>() );
    NT2_TEST_EQUAL( (boost::simd::Mindenormal<vd_t>())[i], boost::simd::Mindenormal<T>() );
    NT2_TEST_EQUAL( (boost::simd::Smallestposval<vd_t>())[i], boost::simd::Smallestposval<T>() );
  }
}

