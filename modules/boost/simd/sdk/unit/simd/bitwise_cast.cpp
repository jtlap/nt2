//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/true.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/detail/endian.hpp>

template<class T> struct bitmask_;

template<> struct bitmask_<float>
{
  static boost::simd::uint32_t value() { return 0x3f800000u; }
};

template<> struct bitmask_<double>
{
  static boost::simd::uint64_t value() { return 0x3ff0000000000000ull; }
};

////////////////////////////////////////////////////////////////////////////////
// Test bitwise_cast
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(floating, BOOST_SIMD_SIMD_REAL_TYPES )
{
  using boost::simd::native;
  using boost::simd::splat;
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
    vT1 ref = splat<vT1>(bitmask_<T>::value());
    NT2_TEST_EQUAL(y,ref);
  }
  {
    T  x = boost::simd::One<T>();
    T1 y = bitwise_cast<T1>(x);
      NT2_TEST_EQUAL(y, bitmask_<T>::value());
  }
  {
    lvT x = boost::simd::True<lvT>();
    lvT1 y = bitwise_cast<lvT1>(x);
    lvT1 ref = splat<lvT1>(true);
    NT2_TEST_EQUAL(y, ref);
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
  using boost::simd::splat;
  using boost::simd::bitwise_cast;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;
  typedef native<uint8_t,BOOST_SIMD_DEFAULT_EXTENSION> v8T;

  vT  x = boost::simd::One<vT>();
  v8T y = bitwise_cast<v8T>(x);

  v8T ref;

  for(std::size_t i=0; i!=v8T::static_size; ++i)
  {
#ifdef BOOST_LITTLE_ENDIAN
    std::size_t j = i;
#else
    std::size_t j = v8T::static_size-i-1;
#endif
      ref[j] = (i % sizeof(T)) ? 0u : 1u;
  }

  NT2_TEST_EQUAL(y, ref);
}
