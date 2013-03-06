//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - cmplx_testing/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of complex.arithmetic components in simd  mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 13/01/2012
///
#include <nt2/include/functions/abs.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/real.hpp>
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

#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>

#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

NT2_TEST_CASE_TPL ( abs_cplx__1_0,   BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                              cT;
  typedef native<T ,ext_t>                             vT;
  typedef native<cT ,ext_t>                           vcT;
  typedef typename nt2::meta::as_imaginary<T>::type   ciT;
  typedef native<ciT ,ext_t>                         vciT;
  typedef typename nt2::meta::as_dry<T>::type          dT;
  typedef native<dT ,ext_t>                           vdT;

  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Inf<vT>(),nt2::Nan<vT>())), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Minf<vT>(), nt2::Zero<vT>())), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Mone<vT>(), nt2::Zero<vT>())), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Nan<vT>(), nt2::Zero<vT>())), nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::One<vT>(), nt2::Zero<vT>())), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Valmax<vT>(), nt2::Zero<vT>())), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Valmin<vT>(), nt2::Zero<vT>())), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Zero<vT>(), nt2::Zero<vT>())), nt2::Zero<vT>());
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::One<vT>(), nt2::One<vT>()))[0], nt2::Sqrt_2<T>(), 1);
  NT2_TEST_EQUAL(nt2::abs(vcT(nt2::Four<vT>(), nt2::Three<vT>())), nt2::Five<vT>());

  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Inf<vciT>())), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Inf<vciT>())   ), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Minf<vciT>())  ), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Mone<vciT>())  ), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Nan<vciT>())   ), nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::One<vciT>())   ), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Valmax<vciT>())), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Valmin<vciT>())), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Zero<vciT>() ) ), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::One<vciT>()   )), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vciT(nt2::Four<vciT>() ) ), nt2::Four<vT>());

  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Inf<vdT>())   ), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Inf<vdT>())   ), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Minf<vdT>())  ), nt2::Inf<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Mone<vdT>())  ), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Nan<vdT>())   ), nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::One<vdT>())   ), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Valmax<vdT>())), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Valmin<vdT>())), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Zero<vdT>())  ), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::One<vdT>())   ), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::abs(vdT(nt2::Four<vdT>())  ), nt2::Four<vT>());

} // end of test for floating_


