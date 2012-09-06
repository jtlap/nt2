/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 constants properties"

#include <boost/simd/include/constants/properties.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4146) // unary minus applied to unsigned
#endif

////////////////////////////////////////////////////////////////////////////////
// Test values for sigmask
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(signmask)
{
  NT2_TEST_EQUAL( boost::simd::Signmask<double>(), -0.   );
  NT2_TEST_EQUAL( boost::simd::Signmask<float>() , -0.f );

  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint64_t>(), 0u );
  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint32_t>(), 0u );
  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint16_t>(), 0u );
  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint8_t >(), 0u );

  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::int64_t>(), boost::simd::int64_t(0x8000000000000000LL) );
  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::int32_t>(), boost::simd::int32_t(0x80000000)            );
  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::int16_t>(), boost::simd::int16_t(0x8000)  );
  NT2_TEST_EQUAL( boost::simd::Signmask<boost::simd::int8_t >(), boost::simd::int8_t(0x80)    );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmax
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(valmax)
{
  NT2_TEST_EQUAL( boost::simd::Valmax<double>() , 1.7976931348623157e+308 );
  NT2_TEST_EQUAL( boost::simd::Valmax<float>()  , float(3.4028235e+38)    );

  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint64_t>(), 0xFFFFFFFFFFFFFFFFULL  );
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint32_t>(), 0xFFFFFFFFUL           );
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint16_t>(), 0xFFFF                 );
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint8_t >(), 0xFF                   );
 
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::int64_t>(), 9223372036854775807LL);
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::int32_t>(), 2147483647           );
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::int16_t>(), 32767                );
  NT2_TEST_EQUAL( boost::simd::Valmax<boost::simd::int8_t >(), 127                  );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmin
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(valmin)
{
  NT2_TEST_EQUAL( boost::simd::Valmin<double>() , -1.7976931348623157e+308);
  NT2_TEST_EQUAL( boost::simd::Valmin<float>()  , float(-3.4028235e+38)   );

  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint64_t>(), 0u );
  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint32_t>(), 0u  );
  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint16_t>(), 0u  );
  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint8_t >(), 0u  );

  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::int64_t>()+1, -9223372036854775807LL );
  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::int32_t>()+1, -2147483647L           );
  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::int16_t>(), -32768                  );
  NT2_TEST_EQUAL( boost::simd::Valmin<boost::simd::int8_t >(), -128                    );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for maxleftshift
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(Maxleftshift)
{
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<double>()       , 63 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<float>()        , 31 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint64_t>(), 63 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint32_t>(), 31 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint16_t>(), 15 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint8_t >(), 7  );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int64_t>() , 63 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int32_t>() , 31 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int16_t>() , 15 );
  NT2_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int8_t >() , 7  );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for IEEE specs
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(ieee)
{
  NT2_TEST_EQUAL( boost::simd::Nbmantissabits<double>() , 52);
  NT2_TEST_EQUAL( boost::simd::Nbmantissabits<float>()  , 23);

  NT2_TEST_EQUAL( boost::simd::Nbexponentbits<double>() , 11);
  NT2_TEST_EQUAL( boost::simd::Nbexponentbits<float>()  , 8  );

  NT2_TEST_EQUAL( boost::simd::Maxexponent<double>(), 1023  );
  NT2_TEST_EQUAL( boost::simd::Maxexponent<float>()  , 127    );

  NT2_TEST_EQUAL( boost::simd::Minexponent<double>(), -1022  );
  NT2_TEST_EQUAL( boost::simd::Minexponent<float>()  , -126  );

  NT2_TEST_EQUAL( boost::simd::Ldexpmask<double>(), 0x7FF0000000000000ll  );
  NT2_TEST_EQUAL( boost::simd::Ldexpmask<float>() , 0x7F800000            );

  NT2_TEST_EQUAL( boost::simd::Nbdigits<double>(), 53 );
  NT2_TEST_EQUAL( boost::simd::Nbdigits<float>() , 24 );
}
////////////////////////////////////////////////////////////////////////////////
// Test values for IEEE specs on integer
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(ieee_ints, BOOST_SIMD_INTEGRAL_TYPES)
{
  NT2_TEST_EQUAL( boost::simd::Nbmantissabits<T>(), T(sizeof(T)*CHAR_BIT));
  NT2_TEST_EQUAL( boost::simd::Nbexponentbits<T>(), T(0) );
  NT2_TEST_EQUAL( boost::simd::Maxexponent<T>()   , T(0) );
  NT2_TEST_EQUAL( boost::simd::Minexponent<T>()   , T(0) );
  NT2_TEST_EQUAL( boost::simd::Ldexpmask<T>()     , T(0) );
  NT2_TEST_EQUAL( boost::simd::Nbdigits<T>()      , T(0) );
}
