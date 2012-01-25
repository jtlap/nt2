//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - arg/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <nt2/toolbox/arithmetic/include/functions/arg.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( arg_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                         cT; 
  typedef native<T ,ext_t>                        vT;
  typedef native<cT ,ext_t>                      vcT;

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
  //  NT2_TEST_EQUAL(arg(viT(1)), nt2::Pio_2<vT>());
} // end of test for floating_
