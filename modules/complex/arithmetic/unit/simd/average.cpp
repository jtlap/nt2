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
#include <nt2/include/functions/abs.hpp>
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
#include <nt2/toolbox/arithmetic/include/functions/average.hpp>

NT2_TEST_CASE_TPL ( average_real__2_0,  BOOST_SIMD_REAL_TYPES)
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
  using boost::simd::native;
  
  // specific values tests
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::Inf<vT>(), nt2::Zero<vT>()), vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), vcT(nt2::Inf<vT>(), nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::Half<vT>(),nt2::Zero<vT>())); 
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::Zero<vT>(),nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())); 
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::Zero<vT>(),nt2::One<vT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>())), vcT(nt2::Half<vT>(),nt2::Half<vT>()));
    NT2_TEST_EQUAL(nt2::average(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>())), vcT(nt2::One<vT>(), nt2::Zero<vT>()));
} // end of test for floating_
