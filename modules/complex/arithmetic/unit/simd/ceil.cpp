//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - ceil/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
/// 
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/cos.hpp>
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

NT2_TEST_CASE_TPL ( abs_cplx__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
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
  double ulpd;
  ulpd=0.0;

  // specific values tests
  {
    typedef vcT r_t; 
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::splat<vcT>(cT(-1.1, -1.6)))[0], cT(-1, -1),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::splat<vcT>(cT(1.1, 1.6)))[0],  cT(2, 2),0);  
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Inf<vcT>())[0], nt2::Inf<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Minf<vcT>())[0], nt2::Minf<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Mone<vcT>())[0], nt2::Mone<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Nan<vcT>())[0], nt2::Nan<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::One<vcT>())[0], nt2::One<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Zero<vcT>())[0], nt2::Zero<cT>(),0);
  }  
  {
    typedef vciT r_t; 
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::splat<vciT>(ciT(-1.1)))[0], nt2::Mone<vciT>()[0],0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::splat<vciT>(ciT(1.1)))[0], nt2::Two<vciT>()[0],0);  
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Inf<vciT>())[0], nt2::Inf<vciT>()[0],0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Minf<vciT>())[0], nt2::Minf<vciT>()[0],0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Mone<vciT>())[0], nt2::Mone<vciT>()[0],0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Nan<vciT>())[0], nt2::Nan<vciT>()[0],0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::One<vciT>())[0], nt2::One<vciT>()[0],0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Zero<vciT>())[0], nt2::Zero<vciT>()[0],0);
  }
  {
    typedef vdT r_t; 
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::splat<vdT>(dT(-1.1)))[0], nt2::Mone<dT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::splat<vdT>(dT(1.1)))[0], nt2::Two<dT>(),0);  
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Inf<vdT>())[0], nt2::Inf<dT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Minf<vdT>())[0], nt2::Minf<dT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Mone<vdT>())[0], nt2::Mone<dT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Nan<vdT>())[0], nt2::Nan<dT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::One<vdT>())[0], nt2::One<dT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::ceil(nt2::Zero<vdT>())[0], nt2::Zero<dT>(),0);
  }
} // end of test for floating_
