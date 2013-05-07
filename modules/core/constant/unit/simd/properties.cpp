//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 constants properties"

#include <nt2/include/constants/properties.hpp>
#include <boost/simd/sdk/simd/native.hpp>
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
  NT2_TEST_EQUAL( nt2::Signmask<double>(), -0.   );
  NT2_TEST_EQUAL( nt2::Signmask<float>() , -0.f );

  NT2_TEST_EQUAL( nt2::Signmask<nt2::uint64_t>(), 0u );
  NT2_TEST_EQUAL( nt2::Signmask<nt2::uint32_t>(), 0u );
  NT2_TEST_EQUAL( nt2::Signmask<nt2::uint16_t>(), 0u );
  NT2_TEST_EQUAL( nt2::Signmask<nt2::uint8_t >(), 0u );

  NT2_TEST_EQUAL( nt2::Signmask<nt2::int64_t>(), nt2::int64_t(0x8000000000000000LL) );
  NT2_TEST_EQUAL( nt2::Signmask<nt2::int32_t>(), nt2::int32_t(0x80000000)           );
  NT2_TEST_EQUAL( nt2::Signmask<nt2::int16_t>(), nt2::int16_t(0x8000)  );
  NT2_TEST_EQUAL( nt2::Signmask<nt2::int8_t >(), nt2::int8_t(0x80)    );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmax
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(valmax)
{
  NT2_TEST_EQUAL( nt2::Valmax<double>() , 1.7976931348623157e+308 );
  NT2_TEST_EQUAL( nt2::Valmax<float>()  , float(3.4028235e+38)    );

  NT2_TEST_EQUAL( nt2::Valmax<nt2::uint64_t>(), 0xFFFFFFFFFFFFFFFFULL  );
  NT2_TEST_EQUAL( nt2::Valmax<nt2::uint32_t>(), 0xFFFFFFFFUL           );
  NT2_TEST_EQUAL( nt2::Valmax<nt2::uint16_t>(), 0xFFFF                 );
  NT2_TEST_EQUAL( nt2::Valmax<nt2::uint8_t >(), 0xFF                   );

  NT2_TEST_EQUAL( nt2::Valmax<nt2::int64_t>(), 9223372036854775807LL);
  NT2_TEST_EQUAL( nt2::Valmax<nt2::int32_t>(), 2147483647           );
  NT2_TEST_EQUAL( nt2::Valmax<nt2::int16_t>(), 32767                );
  NT2_TEST_EQUAL( nt2::Valmax<nt2::int8_t >(), 127                  );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for valmin
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(valmin)
{
  NT2_TEST_EQUAL( nt2::Valmin<double>() , -1.7976931348623157e+308);
  NT2_TEST_EQUAL( nt2::Valmin<float>()  , float(-3.4028235e+38)   );

  NT2_TEST_EQUAL( nt2::Valmin<nt2::uint64_t>(), 0u );
  NT2_TEST_EQUAL( nt2::Valmin<nt2::uint32_t>(), 0u  );
  NT2_TEST_EQUAL( nt2::Valmin<nt2::uint16_t>(), 0u  );
  NT2_TEST_EQUAL( nt2::Valmin<nt2::uint8_t >(), 0u  );

  NT2_TEST_EQUAL( nt2::Valmin<nt2::int64_t>(), int64_t(-9223372036854775808ULL) );
  NT2_TEST_EQUAL( nt2::Valmin<nt2::int32_t>(), int32_t(-2147483648UL)           );
  NT2_TEST_EQUAL( nt2::Valmin<nt2::int16_t>(), int16_t(-32768)                  );
  NT2_TEST_EQUAL( nt2::Valmin<nt2::int8_t >(), int8_t (-128)                    );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for maxleftshift
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(maxleftshift)
{
  NT2_TEST_EQUAL( nt2::Maxleftshift<double>()       , 63 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<float>()        , 31 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::uint64_t>(), 63 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::uint32_t>(), 31 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::uint16_t>(), 15 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::uint8_t >(), 7  );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::int64_t>() , 63 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::int32_t>() , 31 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::int16_t>() , 15 );
  NT2_TEST_EQUAL( nt2::Maxleftshift<nt2::int8_t >() , 7  );
}

////////////////////////////////////////////////////////////////////////////////
// Test values for IEEE specs
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(ieee)
{
  NT2_TEST_EQUAL( nt2::Nbmantissabits<double>() , 52);
  NT2_TEST_EQUAL( nt2::Nbmantissabits<float>()  , 23);

  NT2_TEST_EQUAL( nt2::Nbexponentbits<double>() , 11);
  NT2_TEST_EQUAL( nt2::Nbexponentbits<float>()  , 8  );

  NT2_TEST_EQUAL( nt2::Maxexponent<double>(), 1023  );
  NT2_TEST_EQUAL( nt2::Maxexponent<float>()  , 127    );

  NT2_TEST_EQUAL( nt2::Minexponent<double>(), -1022  );
  NT2_TEST_EQUAL( nt2::Minexponent<float>()  , -126  );

  NT2_TEST_EQUAL( nt2::Ldexpmask<double>(), 0x7FF0000000000000ll  );
  NT2_TEST_EQUAL( nt2::Ldexpmask<float>() , 0x7F800000            );

  NT2_TEST_EQUAL( nt2::Nbdigits<double>(), 53 );
  NT2_TEST_EQUAL( nt2::Nbdigits<float>() , 24 );
}
