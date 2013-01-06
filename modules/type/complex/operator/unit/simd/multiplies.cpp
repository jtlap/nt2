//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Multipliesributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - multiplies/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/include/functions/abs.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ulpdist.hpp>
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
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/extract.hpp>

NT2_TEST_CASE_TPL ( multiplies_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
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

  // specific values tests
  {
    typedef vcT r_t;
    NT2_TEST_EQUAL(nt2::multiplies(vcT(nt2::Inf<vT>(), nt2::Zero<vT>()), vcT(nt2::Inf<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Inf<vT>(), nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vcT(nt2::Zero<vT>(),nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vcT(nt2::Zero<vT>(),nt2::One<vT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::One<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::One<vT>(), nt2::Zero<vT>())[0]);

    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::Inf<vciT>()), vcT(nt2::Inf<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(), nt2::Inf<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::One<vciT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::Zero<vciT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::Zero<vciT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(),nt2::Zero<vT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::One<vciT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], vcT(nt2::Zero<vT>(), nt2::One<vT>())[0]);

    NT2_TEST_EQUAL(nt2::multiplies(nt2::Inf<vdT>(),  vcT(nt2::Inf<vT>(), nt2::Zero<vT>()))[0], cT(nt2::Inf<T>(), nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::One<vdT>(),  vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], cT(nt2::Zero<T>(),nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::Zero<vdT>(), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()))[0], cT(nt2::Zero<T>(),nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::Zero<vdT>(), vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], cT(nt2::Zero<T>(),nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::One<vdT>(),  vcT(nt2::One<vT>(), nt2::Zero<vT>()))[0], cT(nt2::One<T>(), nt2::Zero<T>()));
  }
  {
    typedef vciT r_t;
    NT2_TEST_EQUAL(nt2::multiplies(nt2::Inf<vdT>(),   nt2::Inf<vciT>())[0] , ciT(nt2::Inf<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::One<vdT>(),   nt2::Zero<vciT>())[0], ciT(nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::Zero<vdT>(),  nt2::Zero<vciT>())[0], ciT(nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::Zero<vdT>(),  nt2::One<vciT>())[0] , ciT(nt2::Zero<T>()));
    NT2_TEST_EQUAL(nt2::multiplies(nt2::One<vdT>(),   nt2::One<vciT>())[0] , ciT(nt2::One<T>()));
  }
  {
    typedef vdT r_t;
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::Inf<vciT>()),   vciT(nt2::Inf<vciT>()))[0],  vdT(nt2::Minf<vdT>() )[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::One<vciT>()),   vciT(nt2::Zero<vciT>()))[0], vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::Zero<vciT>()),  vciT(nt2::Zero<vciT>()))[0], vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::Zero<vciT>()),  vciT(nt2::One<vciT>()))[0],  vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vciT(nt2::One<vciT>()),   vciT(nt2::One<vciT>()))[0],  vdT(nt2::Mone<vdT>() )[0]);
  }
  {
    typedef vdT r_t;
    NT2_TEST_EQUAL(nt2::multiplies(vdT(nt2::Inf<vdT>()),   vdT(nt2::Inf<vdT>()))[0],  vdT(nt2::Inf<vdT>() )[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vdT(nt2::One<vdT>()),   vdT(nt2::Zero<vdT>()))[0], vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vdT(nt2::Zero<vdT>()),  vdT(nt2::Zero<vdT>()))[0], vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vdT(nt2::Zero<vdT>()),  vdT(nt2::One<vdT>()))[0],  vdT(nt2::Zero<vdT>())[0]);
    NT2_TEST_EQUAL(nt2::multiplies(vdT(nt2::One<vdT>()),   vdT(nt2::One<vdT>()))[0],  vdT(nt2::One<vdT>() )[0]);
  }
} // end of test for floating_
