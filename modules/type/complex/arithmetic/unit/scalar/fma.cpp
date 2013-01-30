//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - fma/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <nt2/toolbox/arithmetic/include/functions/fma.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/minf.hpp>


NT2_TEST_CASE_TPL ( fma_real__3_0, BOOST_SIMD_REAL_TYPES)
{

  using nt2::fma;
  using nt2::tag::fma_;
  typedef std::complex<T> cT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fma_(cT,cT,cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef cT wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(fma(cT(nt2::Inf<T>()), cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), cT(nt2::Inf<T>()), 0);
  NT2_TEST_EQUAL(fma(cT(nt2::Minf<T>()), cT(nt2::Minf<T>()), cT(nt2::Minf<T>())), cT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Mone<T>()), cT(nt2::Mone<T>()), cT(nt2::Mone<T>())), cT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Nan<T>()), cT(nt2::Nan<T>()), cT(nt2::Nan<T>())), cT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::One<T>()), cT(nt2::One<T>()), cT(nt2::One<T>())), cT(nt2::Two<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Zero<T>()), cT(nt2::Zero<T>()), cT(nt2::Zero<T>())), cT(nt2::Zero<T>()));
} // end of test for floating_



NT2_TEST_CASE_TPL ( fma_various,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::fma;
  using nt2::tag::fma_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef typename nt2::meta::as_imaginary<T>::type iT;

  // specific values tests

  std::cout << "0\n";
  NT2_TEST_EQUAL(fma(T(2), T(3), T(4)), T(10));
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(4)), cT(10));
  NT2_TEST_EQUAL(    cT(2)*cT(3)+cT(4), cT(10));
  std::cout << "1\n";
  NT2_TEST_EQUAL(fma(cT(2), cT(3), iT(4)), cT(6, 4));
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(0, 4)), cT(6, 4));
  NT2_TEST_EQUAL(    cT(2)*cT(3)+cT(0, 4), cT(6, 4));
  std::cout << "2\n";
  NT2_TEST_EQUAL(fma(cT(2), iT(3), cT(4)), cT(4, 6));
  NT2_TEST_EQUAL(fma(cT(2), cT(0, 3), cT(4)), cT(4, 6));
  NT2_TEST_EQUAL((cT(2)*cT(0, 3)+cT(4)), cT(4, 6));
  std::cout << "3\n";
  NT2_TEST_EQUAL(fma(iT(2), cT(3), cT(4)), cT(4, 6));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(3), cT(4)), cT(4, 6));
  NT2_TEST_EQUAL((cT(0, 2)* cT(3)+cT(4)), cT(4, 6));
  std::cout << "4\n";
  NT2_TEST_EQUAL(fma(cT(2), iT(3), iT(4)), cT(0, 10));
  NT2_TEST_EQUAL(fma(cT(2), cT(0, 3), cT(0, 4)), cT(0, 10));
  NT2_TEST_EQUAL((cT(2)* cT(0, 3)+ cT(0, 4)), cT(0, 10));
  std::cout << "5\n";
  NT2_TEST_EQUAL(fma(iT(2), iT(3), cT(4, 5)), cT(-2, 5));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(0, 3), cT(4, 5)), cT(-2, 5));
  NT2_TEST_EQUAL((cT(0, 2)* cT(0, 3)+ cT(4, 5)), cT(-2, 5));
  std::cout << "6\n";
  NT2_TEST_EQUAL(fma(iT(2), cT(3, 5), iT(4)), cT(-10, 10));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(3, 5), cT(0, 4)), cT(-10, 10));
  NT2_TEST_EQUAL((cT(0, 2)* cT(3, 5)+ cT(0, 4)), cT(-10, 10));
  std::cout << "7\n";
  NT2_TEST_EQUAL(fma(iT(2), iT(3),iT(4)), cT(-6, 4));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(0, 3), cT(0, 4)), cT(-6, 4));
  NT2_TEST_EQUAL((cT(0, 2)*cT(0, 3)+cT(0, 4)), cT(-6, 4));
  std::cout << "8\n";
  NT2_TEST_EQUAL(fma(T(2), cT(5, 3),cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL(fma(cT(2), cT(5, 3), cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL((cT(2)*cT(5, 3)+cT(6, 4)), cT(16, 10));
  std::cout << "9\n";
  NT2_TEST_EQUAL(fma(T(2), cT(5, 3),cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL(fma(cT(2), cT(5, 3), cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL((cT(2)*cT(5, 3)+cT(6, 4)), cT(16, 10));
  std::cout << "10\n";
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(5, 3),T(6)), cT(7, 21));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(5, 3), cT(6)), cT(7, 21));
  NT2_TEST_EQUAL((cT(2, 3)*cT(5, 3)+cT(6)), cT(7, 21));
  std::cout << "11\n";
  NT2_TEST_EQUAL(fma(cT(2, 3), T(5),T(6)), cT(16, 15));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(5), cT(6)), cT(16, 15));
  NT2_TEST_EQUAL((cT(2, 3)*cT(5)+cT(6)), cT(16, 15));
  std::cout << "12\n";
  NT2_TEST_EQUAL(fma(T(2), cT(5, 3),T(6)), cT(16, 6));
  NT2_TEST_EQUAL(fma(cT(2), cT(5, 3), cT(6)), cT(16, 6));
  NT2_TEST_EQUAL((cT(2)*cT(5, 3)+cT(6)), cT(16, 6));
  std::cout << "13\n";
  NT2_TEST_EQUAL(fma(T(2), T(5),cT(6, 2)), cT(16, 2));
  NT2_TEST_EQUAL(fma(cT(2), cT(5), cT(6, 2)), cT(16, 2));
  NT2_TEST_EQUAL((cT(2)*cT(5)+cT(6, 2)), cT(16, 2));
  std::cout << "14\n";
  NT2_TEST_EQUAL(fma(T(2), iT(5),cT(6, 2)), cT(6, 12));
  NT2_TEST_EQUAL(fma(cT(2), cT(0, 5), cT(6, 2)), cT(6, 12));
  NT2_TEST_EQUAL((cT(2)*cT(0, 5)+cT(6, 2)), cT(6, 12));
  std::cout << "15\n";
  NT2_TEST_EQUAL(fma(T(2), cT(2, 5),iT(2)), cT(4, 12));
  NT2_TEST_EQUAL(fma(cT(2), cT(2, 5), cT(0, 2)), cT(4, 12));
  NT2_TEST_EQUAL((cT(2)*cT(2, 5)+cT(0, 2)), cT(4, 12));
  std::cout << "16\n";
  NT2_TEST_EQUAL(fma(cT(2, 5), iT(5),T(2)), cT(-23, 10));
  NT2_TEST_EQUAL(fma(cT(2, 5), cT(0, 5), cT(2)), cT(-23, 10));
  NT2_TEST_EQUAL((cT(2, 5)*cT(0, 5)+cT(2)), cT(-23, 10));
  std::cout << "17\n";
  NT2_TEST_EQUAL(fma(iT(5), cT(2, 5),T(2)), cT(-23, 10));
  NT2_TEST_EQUAL(fma(cT(0, 5), cT(2, 5), cT(2)), cT(-23, 10));
  NT2_TEST_EQUAL((cT(0, 5)*cT(2, 5)+cT(2)), cT(-23, 10));
  std::cout << "18\n";
  NT2_TEST_EQUAL(fma(cT(2, 5), T(3),iT(2)), cT(6, 17));
  NT2_TEST_EQUAL(fma(cT(2, 5), cT(3, 0), cT(0, 2)), cT(6, 17));
  NT2_TEST_EQUAL((cT(2, 5)*cT(3, 0)+cT(0, 2)), cT(6, 17));
  std::cout << "19\n";
  NT2_TEST_EQUAL(fma(iT(5), T(3),cT(6, 2)), cT(6, 17));
  NT2_TEST_EQUAL(fma(cT(0, 5), cT(3), cT(6, 2)), cT(6, 17));
  NT2_TEST_EQUAL((cT(0, 5)*cT(3, 0)+cT(6, 2)), cT(6, 17));



} // end of test for floating_

NT2_TEST_CASE_TPL ( fma_various_invalid, (float))//BOOST_SIMD_REAL_TYPES)
{

  using nt2::fma;
  using nt2::tag::fma_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef typename nt2::meta::as_imaginary<T>::type iT;

  // specific values tests

  std::cout << "0 ccc \n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), cT(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), cT(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(4)), cT(10));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(3, 1), cT(2, 4)), cT(5, 15));

  NT2_TEST_EQUAL(fma(cT(0, nt2::Inf<T>()), cT(0), cT(3, 4)), cT(3, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(0),cT(0, nt2::Inf<T>()), cT(4)), cT(4, nt2::Nan<T>()));

  NT2_TEST_EQUAL(fma(cT(1, nt2::Inf<T>()), cT(0), cT(3, nt2::Minf<T>())), cT(3, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(0),cT(1, nt2::Inf<T>()), cT(4)), cT(4, nt2::Nan<T>()));

  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), T(3), T(4)), nt2::Inf<T>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), cT(nt2::Minf<T>())), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(1),nt2::Inf<cT>(), cT(nt2::Minf<T>())), cT(nt2::Nan<T>(), 0));
  NT2_TEST_EQUAL(fma(cT(1),cT(0, nt2::Inf<T>()), cT(nt2::Minf<T>())), cT(nt2::Minf<T>(), nt2::Inf<T>()));

  NT2_TEST_EQUAL(   nt2::multiplies(nt2::Inf<cT>(), cT(3))+cT(4), nt2::Inf<cT>());

  std::cout << "1 cci\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), iT(0)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(0, 4)), cT(6, 4));
  NT2_TEST_EQUAL(    nt2::plus(nt2::multiplies(nt2::Inf<cT>(), cT(3)), iT(0)), nt2::Inf<cT>());

  std::cout << "2 cic \n";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), T(0), cT(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), iT(0), cT(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), cT(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(nt2::Inf<cT>(), iT(0)), cT(4)), nt2::Nan<cT>());
  std::cout << "3 icc\n";
  NT2_TEST_EQUAL(fma(iT(0), nt2::Inf<cT>(), cT(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0), nt2::Inf<cT>(), cT(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(iT(0), nt2::Inf<cT>()), cT(4)), nt2::Nan<cT>());

  std::cout << "4 cii\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), iT(0), cT(0, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), iT(1), iT(4)), cT(0, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0, 1), iT(4)), cT(0, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), cT(0, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(cT(0), cT(0), nt2::Inf<cT>()),  nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), nt2::Inf<cT>()),  nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Minf<cT>(), cT(1), nt2::Inf<cT>()),  nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(1), nt2::Inf<cT>()),  nt2::Nan<cT>());
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(nt2::Inf<cT>(), cT(0)), cT(0, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(nt2::Inf<cT>(), iT(0)), cT(0, 4)), cT(nt2::Nan<T>(), 4));

  std::cout << "5 iic\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), cT(4, 5)), cT(nt2::Nan<T>(), 5));
  NT2_TEST_EQUAL(fma(cT(0), nt2::Inf<cT>(), cT(4, 5)), cT(nt2::Nan<T>(), 5));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(nt2::Inf<cT>(), cT(0)), cT(4, 5)), cT(nt2::Nan<T>(), 5));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(nt2::Inf<cT>(), iT(0)), cT(4, 5)), cT(nt2::Nan<T>(), 5));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(0), cT(4, 4)), cT(4, nt2::Nan<T>()));


  std::cout << "6 ici\n";
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), cT(0), iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(0), iT(nt2::Inf<T>()), iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(0), cT(3, 4)), cT(3, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(iT(0), iT(nt2::Inf<T>()), cT(3, 4)), cT(3, nt2::Nan<T>()));

  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(0), iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma( iT(0),iT(nt2::Inf<T>()),iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(1), iT(4)), cT(nt2::Minf<T>(), 4));
  NT2_TEST_EQUAL(fma( iT(1),iT(nt2::Inf<T>()),iT(4)), cT(nt2::Minf<T>(), 4));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(cT(0,nt2::Inf<T>()), cT(0)), cT(0, 4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(iT(nt2::Inf<T>()), cT(0)), cT(0, 4)), cT(0, nt2::Nan<T>()));

  std::cout << "7 iii\n";
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(3),iT(4)), cT(nt2::Minf<T>(), 4));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(0),iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(iT(nt2::Inf<T>()), iT(0)), iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(iT(nt2::Inf<T>()), iT(3)), iT(4)), cT(nt2::Minf<T>(), 4));

  std::cout << "8\n acc";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), cT(0),cT(6, 4)),     cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), iT(0), cT(6, 4)),    cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), cT(0, 3),cT(6, 4)),  cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), iT(3), cT(6, 4)),    cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(0),          nt2::Inf<cT>(),      cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0),          iT(nt2::Inf<T>()),   cT(6, 4)), cT(6, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  cT(1), cT( 3, 4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma(T(1), cT(nt2::Inf<T>()),  cT(4, 4)), cT(nt2::Inf<T>(), 4));

  std::cout << "9 cac\n";
  NT2_TEST_EQUAL(fma( cT(0)                ,nt2::Inf<T>(),cT(6, 4)),     cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( iT(0)                ,nt2::Inf<T>(),cT(6, 4)),    cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( iT(0)                ,nt2::Inf<cT>(),cT(6, 4)),    cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( cT(0, 3)             ,nt2::Inf<T>(),cT(6, 4)),  cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma( iT(3)                ,nt2::Inf<T>(),cT(6, 4)),    cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma( nt2::Inf<cT>(),       T(0),         cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( iT(nt2::Inf<T>()),    T(0),         cT(6, 4)), cT(6, nt2::Nan<T>()));

  std::cout << "10 cca\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), T(4)),                     nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(3),                     nt2::Inf<cT>(), T(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(4),                     nt2::Inf<cT>(), cT(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), T(4), cT(3)),                     nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), T(4)),                     nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0),                     nt2::Inf<cT>(), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0),                     nt2::Inf<cT>(), cT(3)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), T(4), cT(3)),                     nt2::Inf<cT>());

  std::cout << "11 caa\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), T(3),           T(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(3, 4),        nt2::Inf<T>(), T(4)), cT(nt2::Inf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(cT(4),           nt2::Inf<T>(), T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(),  T(0),          T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0),           nt2::Inf<T>(), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(),  T(4),          T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(0, nt2::Inf<T>()), T(4),     T(3)), cT(3, nt2::Inf<T>()));


  std::cout << "12 aca\n";
  NT2_TEST_EQUAL(fma(T(3),         nt2::Inf<cT>(),   T(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),cT(3, 4),         T(4)), cT(nt2::Inf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),cT(4),            T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(T(0),         nt2::Inf<cT>(),   T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),cT(0),            T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(T(4),         nt2::Inf<cT>(),   T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(T(4), cT(0, nt2::Inf<T>()), T(3)), cT(3, nt2::Inf<T>()));

  std::cout << "13 aac\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  T(0), cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0), nt2::Inf<T>(),  cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  T(1), cT(6, 4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma(T(1), nt2::Inf<T>(),  cT(6, 4)), cT(nt2::Inf<T>(), 4));


  std::cout << "14\n aic";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(0), cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0), iT(nt2::Inf<T>()),  cT(6, 4)), cT(6, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(1), cT(6, 4)), cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(1), iT(nt2::Inf<T>()),  cT(6, 4)), cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(0), cT(6)), cT(nt2::Nan<T>(), 0));
  NT2_TEST_EQUAL(fma(T(0), iT(nt2::Inf<T>()),  cT(6)), cT(6, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(1), cT(6)), cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(1), iT(nt2::Inf<T>()),  cT(6)), cT(6, nt2::Inf<T>()));


  std::cout << "15 aci\n";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  cT(0), iT(4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0), cT(nt2::Inf<T>()),  iT(4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  cT(1), iT(4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma(T(1), cT(nt2::Inf<T>()),  iT(4)), cT(nt2::Inf<T>(), 4));

  std::cout << "16 cia \n";
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), iT(0), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0), iT(nt2::Inf<T>()), T(4)), cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(0), cT(0, nt2::Inf<T>()), T(4)),cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(nt2::Inf<cT>(), iT(0)), T(4)), nt2::Nan<cT>());



  std::cout << "17 ica \n";
  NT2_TEST_EQUAL(fma(iT(0), nt2::Inf<cT>(), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0), nt2::Inf<cT>(), T(4)), nt2::Nan<cT>());


  std::cout << "18 cai \n";
  NT2_TEST_EQUAL(fma( cT(0),              nt2::Inf<T>(), iT(4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( cT(nt2::Inf<T>()),  T(0),          iT(4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( cT(1),              nt2::Inf<T>(), iT(4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma( cT(nt2::Inf<T>()),  T(1),          iT(4)), cT(nt2::Inf<T>(), 4));



  std::cout << "19 iac \n";
  NT2_TEST_EQUAL(fma( iT(0),              nt2::Inf<T>(), cT(6, 4)),   cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( iT(nt2::Inf<T>()),  T(0),          cT(6, 4)), cT(6, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma( iT(1),   nt2::Inf<T>(), cT(6, 4)), cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma( iT(nt2::Inf<T>()),  T(1),          cT(6, 4)), cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma( iT(0),              nt2::Inf<T>(), cT(6)),      cT(nt2::Nan<T>(), 0));
  NT2_TEST_EQUAL(fma( iT(nt2::Inf<T>()),  T(0),          cT(6)), cT(6, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma( iT(1),              nt2::Inf<T>(), cT(6)),      cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma( iT(nt2::Inf<T>()),  T(1),          cT(6)), cT(6, nt2::Inf<T>()));

  std::cout << "20 aai \n";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  T(0), iT(4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0), nt2::Inf<T>(),  iT(4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  T(1), iT(4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma(T(1), nt2::Inf<T>(),  iT(4)), cT(nt2::Inf<T>(), 4));

  std::cout << "21 aia \n";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(0), T(4)),    cT(nt2::Nan<T>(), 0));
  NT2_TEST_EQUAL(fma(T(0), iT(nt2::Inf<T>()),  T(4)), cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(1), T(4)),    cT(4, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(1), iT(nt2::Inf<T>()),  T(4)), cT(4, nt2::Inf<T>()));

  std::cout << "22 iaa \n";
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()),  T(0), T(4)),    cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(iT(0), nt2::Inf<T>(),  T(4)),       cT(nt2::Nan<T>(), 0));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()),  T(1), T(4)),    cT(4, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(iT(1), T(nt2::Inf<T>()),  T(4)),    cT(4, nt2::Inf<T>()));

  std::cout << "23 aii \n";
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(0), iT(4)),    cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0), iT(nt2::Inf<T>()),  iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  iT(1), iT(4)),    cT(0, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(1), iT(nt2::Inf<T>()),  iT(4)), cT(0, nt2::Inf<T>()));

  std::cout << "24 iia \n";
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(3),T(4)), cT(nt2::Minf<T>(), 0));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), iT(0),T(4)), cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(iT(nt2::Inf<T>()), iT(0)), T(4)), cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::plus(nt2::multiplies(iT(nt2::Inf<T>()), iT(3)), T(4)), cT(nt2::Minf<T>(), 0));

  std::cout << "25 iai \n";
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), T(3),iT(4)), cT(0, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(iT(nt2::Inf<T>()), T(0),iT(4)), cT(0, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(iT(3), nt2::Inf<T>(),iT(4)),     cT(0,  nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(iT(0), nt2::Inf<T>(),iT(4)),     cT(nt2::Nan<T>(), 4));
} // end of test for floating_
