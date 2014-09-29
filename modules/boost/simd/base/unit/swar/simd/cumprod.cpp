//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/cumprod.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

template < class vT > vT byhands(const vT & a)
{
  vT that = a;
  for(size_t i=1; i!= boost::simd::meta::cardinal_of<vT>::value; ++i)
    that[i] *= that[i-1];
  return that;
}



NT2_TEST_CASE_TPL ( cumprod_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::cumprod;
  using boost::simd::tag::cumprod_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(cumprod(boost::simd::Inf<vT>()) ,  byhands(boost::simd::Inf<vT>()));
  NT2_TEST_EQUAL(cumprod(boost::simd::Minf<vT>()),  byhands(boost::simd::Minf<vT>()));
  NT2_TEST_EQUAL(cumprod(boost::simd::Nan<vT>()) ,  byhands(boost::simd::Nan<vT>()));
#endif
  NT2_TEST_EQUAL(cumprod(boost::simd::Mone<vT>()), byhands(boost::simd::Mone<vT>()));
  NT2_TEST_EQUAL(cumprod(boost::simd::One<vT>()) , byhands(boost::simd::One<vT>()) );
  NT2_TEST_EQUAL(cumprod(boost::simd::Zero<vT>()), byhands(boost::simd::Zero<vT>()));
  NT2_TEST_EQUAL(cumprod(boost::simd::Two<vT>()),byhands(boost::simd::Two<vT>()) );

} // end of test for floating_

NT2_TEST_CASE_TPL ( cumprod_signed_int__1_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::cumprod;
  using boost::simd::tag::cumprod_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // specific values tests
  NT2_TEST_EQUAL(cumprod(boost::simd::Mone<vT>()),byhands(boost::simd::Mone<vT>()) );
  NT2_TEST_EQUAL(cumprod(boost::simd::One<vT>()) ,byhands(boost::simd::One<vT>())  );
  NT2_TEST_EQUAL(cumprod(boost::simd::Zero<vT>()),byhands(boost::simd::Zero<vT>()) );
  NT2_TEST_EQUAL(cumprod(boost::simd::Two<vT>()),byhands(boost::simd::Two<vT>()) );
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( cumprod_unsigned_int__1_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::cumprod;
  using boost::simd::tag::cumprod_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // specific values tests
  NT2_TEST_EQUAL(cumprod(boost::simd::One<vT>()) ,byhands(boost::simd::One<vT>())  );
  NT2_TEST_EQUAL(cumprod(boost::simd::Zero<vT>()),byhands(boost::simd::Zero<vT>()) );
  NT2_TEST_EQUAL(cumprod(boost::simd::Two<vT>()),byhands(boost::simd::Two<vT>()) );
} // end of test for unsigned_int_
