//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - saturate/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/ieee/include/functions/scalar/saturate.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL ( saturate_small
                  , (boost::int8_t)(boost::int16_t)(boost::int32_t)
                    (boost::uint8_t)(boost::uint16_t)(boost::uint32_t)
                  )
{
  using boost::simd::Zero;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::saturate;

  typedef typename boost::dispatch::meta::upgrade<T,signed>::type   signed_t;
  typedef typename boost::dispatch::meta::upgrade<T,unsigned>::type usigned_t;

  NT2_TEST_EQUAL( saturate<T>( signed_t(Valmin<T>())-1 )  , signed_t(Valmin<T>()) );
  NT2_TEST_EQUAL( saturate<T>( signed_t(Valmin<T>()) )    , signed_t(Valmin<T>()) );
  NT2_TEST_EQUAL( saturate<T>( Zero<signed_t>() )         , Zero<signed_t>()      );
  NT2_TEST_EQUAL( saturate<T>( signed_t(Valmax<T>()) )    , signed_t(Valmax<T>()) );
  NT2_TEST_EQUAL( saturate<T>( signed_t(Valmax<T>()) + 1) , signed_t(Valmax<T>()) );

  NT2_TEST_EQUAL( saturate<T>( Zero<usigned_t>() )         , Zero<usigned_t>()        );
  NT2_TEST_EQUAL( saturate<T>( usigned_t(Valmax<T>()) )    , usigned_t(Valmax<T>())   );
  NT2_TEST_EQUAL( saturate<T>( usigned_t(Valmax<T>()) + 1) , usigned_t(Valmax<T>())   );
}

NT2_TEST_CASE_TPL ( saturate_large
                  , (boost::int8_t)(boost::int16_t)(boost::int32_t)
                    (boost::uint8_t)(boost::uint16_t)(boost::uint32_t)
                  )
{
  using boost::simd::Zero;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::saturate;
  typedef boost::uint64_t u_t;
  typedef boost::int64_t  s_t;

  NT2_TEST_EQUAL( saturate<s_t>( Valmin<T>()) , Valmin<T>() );
  NT2_TEST_EQUAL( saturate<s_t>( Zero<T>()  ) , Zero<T>()   );
  NT2_TEST_EQUAL( saturate<s_t>( Valmax<T>()) , Valmax<T>() );
  NT2_TEST_EQUAL( saturate<u_t>( Valmin<T>()) , Valmin<T>() );
  NT2_TEST_EQUAL( saturate<u_t>( Zero<T>()  ) , Zero<T>()   );
  NT2_TEST_EQUAL( saturate<u_t>( Valmax<T>()) , Valmax<T>() );

  NT2_TEST_EQUAL( saturate<s_t>( Zero<T>()  ) , Zero<T>()   );
  NT2_TEST_EQUAL( saturate<s_t>( Valmax<T>()) , Valmax<T>() );
  NT2_TEST_EQUAL( saturate<u_t>( Zero<T>()  ) , Zero<T>()   );
  NT2_TEST_EQUAL( saturate<u_t>( Valmax<T>()) , Valmax<T>() );
}
