//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - saturate/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <boost/simd/toolbox/ieee/include/functions/saturate.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( saturate
                  , (boost::int8_t)(boost::int16_t)(boost::int32_t)
                    (boost::uint8_t)(boost::uint16_t)(boost::uint32_t)
                  )
{
  using boost::simd::Zero;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::saturate;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               n_t;

  typedef typename boost::dispatch::meta::upgrade<n_t,signed>::type   signed_t;
  typedef typename boost::dispatch::meta::upgrade<n_t,unsigned>::type usigned_t;
  typedef typename boost::dispatch::meta::upgrade<T,signed>::type   ssigned_t;
  typedef typename boost::dispatch::meta::upgrade<T,unsigned>::type susigned_t;

  NT2_TEST_EQUAL( saturate<n_t>( splat<signed_t>( ssigned_t(Valmin<T>())-1) )
                , splat<signed_t>(Valmin<T>())
                );

  NT2_TEST_EQUAL( saturate<n_t>( splat<signed_t>( ssigned_t(Valmin<T>())) )
                , splat<signed_t>(Valmin<T>())
                );

  NT2_TEST_EQUAL( saturate<n_t>( Zero<signed_t>() )
                , Zero<signed_t>()
                );

  NT2_TEST_EQUAL( saturate<n_t>( splat<signed_t>(Valmax<T>()) )
                , splat<signed_t>(Valmax<T>())
                );

  NT2_TEST_EQUAL( saturate<n_t>( splat<signed_t>( ssigned_t(Valmax<T>()) + 1))
                , splat<signed_t>(Valmax<T>())
                );

  NT2_TEST_EQUAL( saturate<n_t>( Zero<usigned_t>() )
                , Zero<usigned_t>()
                );

  NT2_TEST_EQUAL( saturate<n_t>( splat<usigned_t>(Valmax<T>()) )
                , splat<usigned_t>(Valmax<T>())
                );

  NT2_TEST_EQUAL( saturate<n_t>( splat<usigned_t>( ssigned_t(Valmax<T>()) + 1))
                , splat<usigned_t>(Valmax<T>())
                );
}
