//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/real_splat.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

#ifdef BOOST_MSVC
  #pragma warning(disable: 4146) // unary minus applied to unsigned
  #pragma warning(disable: 4310) // cast truncate constants
#endif

NT2_TEST_CASE_TPL(allbits_real, BOOST_SIMD_REAL_TYPES)
{
  NT2_TEST_EXPR_TYPE( (boost::simd::Allbits<T>())
                    , boost::mpl::_
                    , T
                    );

  NT2_TEST( check_is_nan(boost::simd::Allbits<T>()) );
}

NT2_TEST_CASE_TPL(allbits_unsigned, BOOST_SIMD_INTEGRAL_TYPES)
{
  NT2_CHECK_CONSTANT(Allbits , ~T(0UL) ,T);
}

NT2_TEST_CASE_TPL(bitincrement_real, BOOST_SIMD_REAL_TYPES)
{
  NT2_TEST_EXPR_TYPE( (boost::simd::Bitincrement<T>())
                    , boost::mpl::_
                    , T
                    );

  NT2_TEST_EQUAL( boost::simd::Bitincrement<T>()
                , (boost::simd::real_constant<T,1,1>())
                );
}

NT2_TEST_CASE_TPL(bitincrement_unsigned, BOOST_SIMD_INTEGRAL_TYPES)
{
  NT2_CHECK_CONSTANT(Bitincrement , T(1) ,T);
}

NT2_TEST_CASE(signmask_real)
{
  NT2_CHECK_CONSTANT(Signmask , -0. ,double);
  NT2_CHECK_CONSTANT(Signmask , -0.f,float);
}

NT2_TEST_CASE_TPL(signmask_unsigned, BOOST_SIMD_UNSIGNED_TYPES)
{
  NT2_CHECK_CONSTANT(Signmask , T(0) ,T);
}

NT2_TEST_CASE_TPL(signmask_signed, BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  NT2_CHECK_CONSTANT(Signmask, (T(1) << (CHAR_BIT*sizeof(T)-1)) ,T);
}

NT2_TEST_CASE(sqrtvalmax_real)
{
  NT2_CHECK_CONSTANT(Sqrtvalmax , 1.3407807929942600077e+154, double);
  NT2_CHECK_CONSTANT(Sqrtvalmax , 18446744073709551616.f    , float);
}

NT2_TEST_CASE_TPL(sqrtvalmax_unsigned, BOOST_SIMD_UNSIGNED_TYPES)
{
  NT2_CHECK_CONSTANT(Sqrtvalmax , T( (T(1) << (CHAR_BIT*sizeof(T)/2))-1) ,T);
}

NT2_TEST_CASE(sqrtvalmax_signed)
{
  NT2_CHECK_CONSTANT(Sqrtvalmax, 3037000499ll , boost::simd::int64_t);
  NT2_CHECK_CONSTANT(Sqrtvalmax,      46340   , boost::simd::int32_t);
  NT2_CHECK_CONSTANT(Sqrtvalmax,        181   , boost::simd::int16_t);
  NT2_CHECK_CONSTANT(Sqrtvalmax,         11   , boost::simd::int8_t );
}

NT2_TEST_CASE(valmax_real)
{
  NT2_CHECK_CONSTANT(Valmax , 1.7976931348623157e+308 , double);
  NT2_CHECK_CONSTANT(Valmax , float(3.4028235e+38)    , float);
}

NT2_TEST_CASE_TPL(valmax_unsigned, BOOST_SIMD_UNSIGNED_TYPES)
{
  NT2_CHECK_CONSTANT(Valmax , T(~(T(0))) ,T);
}

NT2_TEST_CASE_TPL(valmax_signed, BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  NT2_CHECK_CONSTANT(Valmax, T(~(T(1) << (CHAR_BIT*sizeof(T)-1))),T);
}

NT2_TEST_CASE(valmin_real)
{
  NT2_CHECK_CONSTANT(Valmin , -1.7976931348623157e+308 , double);
  NT2_CHECK_CONSTANT(Valmin , float(-3.4028235e+38)    , float);
}

NT2_TEST_CASE_TPL(valmin_unsigned, BOOST_SIMD_UNSIGNED_TYPES)
{
  NT2_CHECK_CONSTANT(Valmin , T(0) ,T);
}

NT2_TEST_CASE_TPL(valmin_signed, BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  typedef typename boost::dispatch::meta::as_unsigned<T>::type u_t;

  NT2_CHECK_CONSTANT(Valmin, T( -u_t(T(1) << (CHAR_BIT*sizeof(T)-1)) ),T);
}

NT2_TEST_CASE_TPL(Maxleftshift, BOOST_SIMD_TYPES)
{
  using boost::dispatch::meta::as_integer;

  NT2_TEST_EXPR_TYPE( boost::simd::Maxleftshift<T>()
                    , boost::mpl::_
                    , (typename as_integer<T,signed>::type)
                    );

  NT2_TEST_EQUAL( boost::simd::Maxleftshift<T>()
                , (typename as_integer<T,signed>::type(CHAR_BIT*sizeof(T)-1))
                );
}

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

NT2_TEST_CASE_TPL(ieee_ints, BOOST_SIMD_INTEGRAL_TYPES)
{
  NT2_CHECK_CONSTANT(Nbmantissabits , T(sizeof(T)*CHAR_BIT) , T);
  NT2_CHECK_CONSTANT(Nbexponentbits , T(0)                  , T);
  NT2_CHECK_CONSTANT(Maxexponent    , T(0)                  , T);
  NT2_CHECK_CONSTANT(Minexponent    , T(0)                  , T);
  NT2_CHECK_CONSTANT(Ldexpmask      , T(0)                  , T);
  NT2_CHECK_CONSTANT(Nbdigits       , T(0)                  , T);
}
