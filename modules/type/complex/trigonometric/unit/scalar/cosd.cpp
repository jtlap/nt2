//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 cosdonential toolbox - cosd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of cosdonential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functions/cos.hpp>
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


  const int N = 20;
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),//0
      cT(nt2::Inf<T>(),nt2::Zero<T>()), //1
      cT(nt2::Minf<T>(),nt2::Zero<T>()),//2
      cT(nt2::Nan<T>(),nt2::Zero<T>()), //3
      cT(nt2::Zero<T>(),nt2::Inf<T>()), //4
      cT(nt2::Inf<T>(),nt2::Inf<T>()),  //5
      cT(nt2::Minf<T>(),nt2::Inf<T>()), //6
      cT(nt2::Nan<T>(),nt2::Inf<T>()),  //7
      cT(nt2::Zero<T>(),nt2::Minf<T>()),//8
      cT(nt2::Inf<T>(),nt2::Minf<T>()), //9
      cT(nt2::Minf<T>(),nt2::Minf<T>()),//10
      cT(nt2::Nan<T>(),nt2::Minf<T>()), //11
      cT(nt2::Zero<T>(),nt2::Nan<T>()), //12
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //13
      cT(nt2::Minf<T>(),nt2::Nan<T>()), //14
      cT(nt2::Nan<T>(),nt2::Nan<T>()),  //15
      cT(nt2::Zero<T>(),180),           //16
      cT(nt2::Inf<T>(),180),            //17
      cT(nt2::Minf<T>(),180),           //18
      cT(nt2::Nan<T>(),180),            //19
    };

  for(int i=0; i < N; i++)
   {
     std::cout << i << std::endl;
     NT2_TEST_ULP_EQUAL(nt2::cosd(-inputs[i]), nt2::cosd(inputs[i]), 3);
     NT2_TEST_ULP_EQUAL(nt2::cosd(inputs[i]), nt2::cos(nt2::multiplies(nt2::Deginrad<T>(), inputs[i])), 3);
   }


 } // end of test for floating_

