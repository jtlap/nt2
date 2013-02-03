//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - rec/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of complex.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/include/functions/rec.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>

NT2_TEST_CASE_TPL ( rec_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::rec;
  using boost::simd::tag::rec_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<rec_(cT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::as_dry<T>::type dT;

  // return type conformity test
  NT2_TEST_EXPR_TYPE( nt2::rec(cT(1))
                    , boost::mpl::_
                    , (cT)
                    );

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

   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::Nan<T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::One<T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::One<T>(), nt2::Nan<T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::Zero<T>())), cT(nt2::Nan<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Nan<T>())), cT(nt2::Zero<T>(), nt2::Nan<T>()));

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

