//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 cosdonential toolbox - cosd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of cosdonential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// 
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/constants/deginrad.hpp>
#include <complex>



NT2_TEST_CASE_TPL ( cosd_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::cosd;
  using nt2::tag::cosd_;
  typedef std::complex<T> cT; 
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<cosd_(cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(1, 1)),std::cos(nt2::Deginrad<T>()*cT(1.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(1, 10)),std::cos(nt2::Deginrad<T>()*cT(1.0, 10.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(10, 1)),std::cos(nt2::Deginrad<T>()*cT(10.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(10, 10)),std::cos(nt2::Deginrad<T>()*cT(10.0, 10.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(0, 1)),std::cos(nt2::Deginrad<T>()*cT(0.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(0, 10)),std::cos(nt2::Deginrad<T>()*cT(0.0, 10.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::cosd(cT(10, 0)),std::cos(nt2::Deginrad<T>()*cT(10.0, 0.0)), 2);
 } // end of test for floating_

