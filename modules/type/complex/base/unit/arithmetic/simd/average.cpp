//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Averageributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - average/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/include/functions/average.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/extract.hpp>

NT2_TEST_CASE_TPL ( average_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                              cT;
  typedef native<T ,ext_t>                             vT;
  typedef native<cT ,ext_t>                           vcT;
  typedef typename nt2::meta::as_dry<T>::type          dT;
  typedef native<dT ,ext_t>                           vdT;

  // specific values tests
  {
    typedef vcT r_t;
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::Inf<vT>(), nt2::Zero<vT>()), vcT(nt2::Inf<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Inf<vT>(), nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Half<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::Zero<vT>(),nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::Zero<vT>(),nt2::One<vT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Half<vT>(),nt2::Half<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::One<vT>(), nt2::Zero<vT>())[0]);

    NT2_TEST_EQUAL(nt2::average(vdT(nt2::Inf<vdT>()),  vcT(nt2::Inf<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Inf<vT>(), nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::One<vdT>()),  vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Half<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::Zero<vdT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::Zero<vdT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Half<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::One<vdT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::One<vT>(), nt2::Zero<vT>())[0]);

  }
  {
    typedef vdT r_t;
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::Inf<vdT>()),   vdT(nt2::Inf<vdT>()))[0],  vdT(nt2::Inf<vdT>() )[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::One<vdT>()),   vdT(nt2::Zero<vdT>()))[0], vdT(nt2::Half<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::Zero<vdT>()),  vdT(nt2::Zero<vdT>()))[0], vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::Zero<vdT>()),  vdT(nt2::One<vdT>()))[0],  vdT(nt2::Half<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::average(vdT(nt2::One<vdT>()),   vdT(nt2::One<vdT>()))[0],  vdT(nt2::One<vdT>() )[0]);
  }
} // end of test for floating_
