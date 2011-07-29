/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "nt2 constants properties"

#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>

#ifdef BOOST_MSVC
  #pragma warning(disable: 4146) // unary minus applied to unsigned
#endif

////////////////////////////////////////////////////////////////////////////////
// Test values for sigmask
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(signmask)
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<double>(), -0.   );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<float>() , -0.f );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint64_t>(), 0 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint32_t>(), 0 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint16_t>(), 0 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::uint8_t >(), 0 );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::int64_t>(), 0x8000000000000000LL );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::int32_t>(), 0x80000000            );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::int16_t>(), boost::simd::int16_t(0x8000)  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Signmask<boost::simd::int8_t >(), boost::simd::int8_t(0x80)    );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmax
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(valmax)
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<double>() , 1.7976931348623157e+308 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<float>()  , float(3.4028235e+38)    );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint64_t>(), 0xFFFFFFFFFFFFFFFFULL  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint32_t>(), 0xFFFFFFFFUL           );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint16_t>(), 0xFFFF                 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::uint8_t >(), 0xFF                   );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::int64_t>(), 9223372036854775807LL);
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::int32_t>(), 2147483647           );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::int16_t>(), 32767                );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmax<boost::simd::int8_t >(), 127                  );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmin
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(valmin)
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<double>() , -1.7976931348623157e+308);
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<float>()  , float(-3.4028235e+38)   );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint64_t>(), 0 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint32_t>(), 0  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint16_t>(), 0  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::uint8_t >(), 0  );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::int64_t>(), -9223372036854775808ULL );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::int32_t>(), -2147483648UL           );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::int16_t>(), -32768                  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Valmin<boost::simd::int8_t >(), -128                    );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for maxleftshift
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(maxleftshift)
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<double>()       , 63 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<float>()        , 31 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint64_t>(), 63 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint32_t>(), 31 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint16_t>(), 15 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::uint8_t >(), 7  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int64_t>() , 63 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int32_t>() , 31 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int16_t>() , 15 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxleftshift<boost::simd::int8_t >() , 7  );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for IEEE specs
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE(ieee)
{
  BOOST_SIMD_TEST_EQUAL( boost::simd::Nbmantissabits<double>() , 52);
  BOOST_SIMD_TEST_EQUAL( boost::simd::Nbmantissabits<float>()  , 23);

  BOOST_SIMD_TEST_EQUAL( boost::simd::Nbexponentbits<double>() , 11);
  BOOST_SIMD_TEST_EQUAL( boost::simd::Nbexponentbits<float>()  , 8  );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxexponent<double>(), 1023  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Maxexponent<float>()  , 127    );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Minexponent<double>(), -1022  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Minexponent<float>()  , -126  );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Ldexpmask<double>(), 0x7FF0000000000000ll  );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Ldexpmask<float>() , 0x7F800000            );

  BOOST_SIMD_TEST_EQUAL( boost::simd::Nbdigits<double>(), 53 );
  BOOST_SIMD_TEST_EQUAL( boost::simd::Nbdigits<float>() , 24 );
}
