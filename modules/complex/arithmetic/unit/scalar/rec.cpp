//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - rec/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/functions/rec.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rec_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::rec;
  using boost::simd::tag::rec_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<rec_(cT)>::type r_t;
  typedef typename nt2::meta::as_imaginary<T>::type ciT;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_dry<T>::type dT;
  typedef cT wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
 ulpd=0.0; 

  // std::cout << nt2::type_id(nt2::I<T>()) << std::endl; 
  // specific values tests
   NT2_TEST_EQUAL(nt2::rec(cT(1)), T(1));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Inf<T>(), nt2::Inf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Minf<T>(), nt2::Minf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Inf<T>(), nt2::Zero<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Inf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Minf<T>(), nt2::Zero<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Minf<T>())), cT(nt2::Zero<cT>()));
   
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Mzero<T>(), nt2::Zero<T>())), cT(nt2::Minf<cT>()));
   
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::Nan<T>())), cT(nt2::Nan<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::One<T>())), cT(nt2::Nan<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::One<T>(), nt2::Nan<T>())), cT(nt2::Nan<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::Zero<T>())), cT(nt2::Nan<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Nan<T>())), cT(nt2::Nan<cT>()));
   
   std::complex < T > a(1, 0);
   NT2_TEST_EQUAL(nt2::rec(a), nt2::One<T>());
   std::complex < T > b(1, 1);
   NT2_TEST_ULP_EQUAL(nt2::rec(b), cT(0.5, -0.5), 0);
   //    NT2_TEST_ULP_EQUAL(rec(nt2::Inf<dT>()), dT(nt2::Zero<T>()), 0);
   //    NT2_TEST_ULP_EQUAL(rec(nt2::Minf<dT>()), dT(nt2::Zero<T>()), 0);
   //    NT2_TEST_ULP_EQUAL(rec(nt2::Mone<dT>()), dT(nt2::Mone<T>()), 0);
   //    NT2_TEST_ULP_EQUAL(rec(nt2::Nan<dT>()), dT(nt2::Nan<T>()), 0);
   //    NT2_TEST_ULP_EQUAL(rec(nt2::One<dT>()), dT(nt2::One<T>()), 0);
   //    NT2_TEST_ULP_EQUAL(rec(nt2::Zero<dT>()), dT(nt2::Inf<T>()), 0);
} // end of test for floating_

