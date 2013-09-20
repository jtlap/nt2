//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/rshl.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/eight.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( rshl_signed,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::rshl;
  using boost::simd::tag::rshl_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type uT;

  typedef native<T,ext_t>               vT;
  typedef native<iT,ext_t>              ivT;
  typedef native<uT,ext_t>              uvT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<rshl_(vT,ivT)>::type
                  , vT
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<rshl_(vT,uvT)>::type
                  , vT
                  );

  // rshl with positive shift
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(), boost::simd::Three<ivT>()), boost::simd::Eight<vT>() );
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(), boost::simd::Three<uvT>()), boost::simd::Eight<vT>() );

  // rshl with negative shift
  NT2_TEST_EQUAL(rshl(boost::simd::Eight<vT>(), -boost::simd::Three<vT>()), boost::simd::One<vT>() );
}

NT2_TEST_CASE_TPL ( rshl_unsigned,  BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES)
{
  using boost::simd::rshl;
  using boost::simd::tag::rshl_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;

  typedef native<T,ext_t>               vT;
  typedef native<iT,ext_t>              ivT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<rshl_(vT,ivT)>::type
                  , vT
                  );


  // rshl with positive shift
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(), boost::simd::Three<ivT>()), boost::simd::Eight<vT>() );
}
