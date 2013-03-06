//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - arg/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/arithmetic/include/functions/arg.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

NT2_TEST_CASE_TPL ( arg_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                         cT;
  typedef native<T ,ext_t>                        vT;
  typedef native<cT ,ext_t>                      vcT;
  typedef typename nt2::meta::as_imaginary<T>::type   ciT;
  typedef native<ciT ,ext_t>                         vciT;
  typedef typename nt2::meta::as_dry<T>::type          dT;
  typedef native<dT ,ext_t>                           vdT;

  // specific values tests
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Minf<vT>(), nt2::Zero<vT>())),nt2::Pi<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Nan<vT>(), nt2::Zero<vT>())), nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::One<vT>(), nt2::Zero<vT>())), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Zero<vT>(), nt2::Zero<vT>())),nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Zero<vT>(), nt2::One<vT>())),  nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::One<vT>(), nt2::Zero<vT>())),  nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Two<vT>(), nt2::Two<vT>())),   nt2::Pio_2<vT>()/nt2::Two<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Two<vT>(),nt2::Mtwo<vT>())),  -nt2::Pio_2<vT>()/nt2::Two<vT>());

  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Inf<vciT>()))  , nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Minf<vciT>())) , -nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Nan<vciT>()))  , nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::One<vciT>()))  , nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Zero<vciT>())) , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Two<vciT>()))  , nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Mone<vciT>()))  , -nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Mzero<vciT>())) , -nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vciT(nt2::Mtwo<vciT>()))  , -nt2::Pio_2<vT>());

  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Inf<vdT>()))  , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Minf<vdT>())) , nt2::Pi<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Nan<vdT>()))  , nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::One<vdT>()))  , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Zero<vdT>())) , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Two<vdT>()))  , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Mone<vdT>())) ,nt2::Pi<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Mzero<vdT>())),nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Mtwo<vdT>())) ,nt2::Pi<vT>());

} // end of test for floating_
