//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - log/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// 
#include <nt2/toolbox/exponential/include/functions/log.hpp>
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


NT2_TEST_CASE_TPL ( log_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::log;
  using nt2::tag::log_;
  typedef std::complex<T> cT; 
  typedef typename nt2::meta::call<log_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Inf<cT>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Minf<cT>()), cT(nt2::Inf<T>(), nt2::Pi<T>()), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Mone<cT>()), cT(nt2::Zero<T>(), nt2::Pi<T>()), 0); 
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Nan<cT>()),  cT(nt2::Nan<T>(), nt2::Nan<T>()), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan<T>(), nt2::Nan<T>())),  cT(nt2::Nan<T>(), nt2::Nan<T>()), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::One<cT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Zero<cT>()), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Mzero<cT>()), cT(nt2::Minf<T>(), nt2::Pi<T>()), 0);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Zero<T>(), nt2::One<T>())),cT(nt2::Zero<T>(), nt2::Pio_2<T>()), 0);

  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Mzero<T>(), nt2::Zero<T>())),  cT(nt2::Minf<T>(), nt2::Pi<T>()), 0.75); 
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Zero<T>(),  nt2::Zero<T>())),  cT(nt2::Minf<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), nt2::Zero<T>())),  cT(nt2::Inf<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), nt2::Zero<T>())),  cT(nt2::Inf<T>(), nt2::Pi<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), nt2::Zero<T>())),  cT(nt2::Inf <T>(), nt2::Zero <T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);

  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Inf<T>(), nt2::Pio_2<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Inf<T>(), nt2::Zero<T>()), 0.75);    
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), nt2::One<T>())),  cT(nt2::Inf<T>(), nt2::Pi<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Inf <T>(), nt2::Zero <T>()), 0.75);   
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), nt2::Inf<T>())),  cT(nt2::Inf <T>(), 3*nt2::Pi<T>()/4), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Inf <T>(), nt2::Pi<T>()/4), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), nt2::Nan<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), nt2::Mone<T>())), cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
  
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::One  <T>(), -nt2::Inf <T>())), cT(nt2::Inf<T>(), -nt2::Pio_2<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::One  <T>(), -nt2::Nan <T>())), cT(nt2::Nan<T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), -nt2::One <T>())), cT(nt2::Inf<T>(), -nt2::Zero<T>()), 0.75);    
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), -nt2::One<T>())),  cT(nt2::Inf<T>(), -nt2::Pi<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), -nt2::One <T>())), cT(nt2::Inf <T>(), -nt2::Zero <T>()), 0.75);   
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), -nt2::Inf<T>())),  cT(nt2::Inf <T>(), -3*nt2::Pi<T>()/4), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), -nt2::Inf<T>())),  cT(nt2::Inf <T>(), -nt2::Pi<T>()/4), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Minf <T>(), -nt2::Nan<T>())),  cT(nt2::Inf <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Inf  <T>(), -nt2::Nan<T>())),  cT(nt2::Inf <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), -nt2::One<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), -nt2::Mone<T>())), cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), -nt2::Inf<T>())),  cT(nt2::Inf <T>(), -nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::log(cT(nt2::Nan  <T>(), -nt2::Nan<T>())),  cT(nt2::Inf <T>(), -nt2::Nan<T>()), 0.75);
} // end of test for floating_

//  clog(conj(z)) = conj(clog(z)).
//  clog($B!](B0 + i0) returns $B!](Binf + i piand raises the -F¡¡divide-by-zero¢¢ floating-point-A
// exception.
//  clog(+0 + i0) returns $B!](Binf + i0 and raises the -F¡¡divide-by-zero¢¢ floating-point-A
// exception.
//  clog(x + i inf) returns +inf + i pi/2, for finite x.
//  clog(x + iNaN) returns NaN + iNaN and optionally raises the -F¡¡invalid¢¢ floating--A
// point exception, for finite x.
//  clog($B!](Binf + iy) returns +inf + i pi, for finite positive-signed y.
//  clog(+inf + iy) returns +inf + i0, for finite positive-signed y.
//  clog($B!](Binf + i inf) returns +inf + i3 pi /4.
//  clog(+inf + i inf) returns +inf + i pi/4.
//  clog(±inf + iNaN) returns +inf + iNaN.
//  clog(NaN + iy) returns NaN + iNaN and optionally raises the -F¡¡invalid¢¢ floating--A
// point exception, for finite y.
//  clog(NaN + i inf) returns +inf + iNaN.
//  clog(NaN + iNaN) returns NaN + iNaN.

