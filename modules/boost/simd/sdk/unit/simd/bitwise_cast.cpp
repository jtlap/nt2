/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::bitwise_cast"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/detail/endian.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test bitwise_cast
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(floating, BOOST_SIMD_SIMD_REAL_TYPES )
{
  using boost::simd::native;
  using boost::simd::bitwise_cast;
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>   vT;
  typedef typename boost::simd::meta::as_logical<T>::type  lT;
  typedef typename boost::simd::meta::as_logical<vT>::type  lvT;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type T1;
  typedef native<T1,BOOST_SIMD_DEFAULT_EXTENSION>   vT1;
  typedef typename boost::simd::meta::as_logical<T1>::type  lT1;
  typedef typename boost::simd::meta::as_logical<vT1>::type  lvT1;
  {
    vT  x = boost::simd::One<vT>();
    vT1 y = bitwise_cast<vT1>(x);
    for(std::size_t i=0; i!=vT::static_size; ++i)
      if(boost::is_same<T, float>::value)
        NT2_TEST_EQUAL(y[i], 0x3f800000u);
      else
        NT2_TEST_EQUAL(y[i], 0x3ff0000000000000ull);
  }
  {
    T  x = boost::simd::One<T>();
    T1 y = bitwise_cast<T1>(x);
    if(boost::is_same<T, float>::value)
      NT2_TEST_EQUAL(y, 0x3f800000u);
    else
      NT2_TEST_EQUAL(y, 0x3ff0000000000000ull);
  }
  {
    lvT x = boost::simd::True<lvT>();
    lvT1 y = bitwise_cast<lvT1>(x);
    for(std::size_t i=0; i!=vT::static_size; ++i)
      NT2_TEST_EQUAL(y[i], boost::simd::logical<T1>(true));
  }
  {
    lT x = boost::simd::True<lT>();
    lT1 y = bitwise_cast<lT1>(x);
    NT2_TEST_EQUAL(y, boost::simd::logical<T1>(true));
  }
}

NT2_TEST_CASE_TPL(integer, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  using boost::simd::native;
  using boost::simd::bitwise_cast;
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;
  typedef native<uint8_t,BOOST_SIMD_DEFAULT_EXTENSION> v8T;
  vT  x = boost::simd::One<vT>();
  v8T y = bitwise_cast<v8T>(x);
  for(std::size_t i=0; i!=v8T::static_size; ++i)
  {
#ifdef BOOST_LITTLE_ENDIAN
    std::size_t j = i;
#else
    std::size_t j = v8T::static_size-i-1;
#endif
    if(i % sizeof(T))
      NT2_TEST_EQUAL(y[j], 0u);
    else
      NT2_TEST_EQUAL(y[j], 1u);
  }
}
