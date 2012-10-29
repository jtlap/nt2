//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - ceil/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
/// 
#include <nt2/toolbox/arithmetic/include/functions/ceil.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/complex/dry.hpp>


NT2_TEST_CASE_TPL ( ceil_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using nt2::ceil;
  using nt2::tag::ceil_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ceil_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef typename nt2::meta::as_imaginary<T>::type ciT;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );

  // specific values tests
  NT2_TEST_EQUAL(ceil(cT(T(-1.1))), T(-1));
  NT2_TEST_EQUAL(ceil(cT(T(1.1))), T(2));
  NT2_TEST_EQUAL(ceil(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Nan<cT>()), nt2::Nan<cT>());
  NT2_TEST_EQUAL(ceil(nt2::One<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Zero<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ceil(dT(T(-1.1))), T(-1));
  NT2_TEST_EQUAL(ceil(dT(T(1.1))), T(2));
  NT2_TEST_EQUAL(ceil(dT(nt2::Inf<T>())), dT(nt2::Inf<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Minf<T>())), dT(nt2::Minf<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Mone<T>())), dT(nt2::Mone<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Nan<T>())), dT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::One<T>())), dT(nt2::One<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Zero<T>())), dT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(ceil(ciT(T(-1.1))), ciT(-1));
  NT2_TEST_EQUAL(ceil(ciT(T(1.1))), ciT(2));
  NT2_TEST_EQUAL(ceil(nt2::Inf<ciT>()), nt2::Inf<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Minf<ciT>()), nt2::Minf<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Mone<ciT>()), nt2::Mone<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Nan<ciT>()), nt2::Nan<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::One<ciT>()), nt2::One<ciT>());
  NT2_TEST_EQUAL(ceil(nt2::Zero<ciT>()), nt2::Zero<ciT>());
} // end of test for floating_
