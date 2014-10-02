//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ror.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( ror_integer, BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;
  using boost::simd::native;
  using boost::simd::One;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                       ext_t;
  typedef native<T,ext_t>                                       vT;
  typedef typename boost::dispatch::meta::as_integer< T>::type  iT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type ivT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(vT,ivT)>::type
                  , vT
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(vT,iT)>::type
                  , vT
                  );

  int w = sizeof(T)*CHAR_BIT;

  for(int i=0;i<w;++i)
    NT2_TEST_EQUAL(ror(One<vT>(),iT(i)), splat<vT>( T(T(1)<<((w-i) & (w-1))) ));

  // Test for error in rotation counts
  ivT one_small = One<ivT>();
  one_small[0]  = iT(-1);
  NT2_TEST_ASSERT(ror(One<vT>(), one_small) );

  ivT one_big  = One<ivT>();
  one_big[1]   = iT(w+1);
  NT2_TEST_ASSERT(ror(One<vT>(), one_big)   );
}

NT2_TEST_CASE_TPL ( ror_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;
  using boost::simd::native;
  using boost::simd::One;
  using boost::simd::splat;
  using boost::simd::bitwise_cast;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                       ext_t;
  typedef native<T,ext_t>                                       vT;
  typedef typename boost::dispatch::meta::as_integer< T>::type  iT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type ivT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(vT,ivT)>::type
                  , vT
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<ror_(vT,iT)>::type
                  , vT
                  );

  int w = sizeof(T)*CHAR_BIT;

  for(int i=0;i<w;++i)
    NT2_TEST_EQUAL( ror( bitwise_cast<vT>(One<ivT>()),iT(i))
                  , bitwise_cast<vT>(splat<ivT>( iT(iT(1)<<((w-i) & (w-1))) ))
                  );

  // Test for error in rotation counts
  ivT one_small = One<ivT>();
  one_small[0]  = -1;
  NT2_TEST_ASSERT(ror(One<vT>(), one_small) );

  ivT one_big  = One<ivT>();
  one_big[1]   = w+1;
  NT2_TEST_ASSERT(ror(One<vT>(), one_big)   );
}
