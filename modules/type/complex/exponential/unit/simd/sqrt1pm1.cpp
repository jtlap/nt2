//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - sqrt1pm1/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// 
#include <nt2/include/functions/sqrt1pm1.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/extract.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

NT2_TEST_CASE_TPL ( sqrt1pm1_real__1_0,  NT2_REAL_TYPES)
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
  double ulpd;
  ulpd=0.0;

  // specific values tests
  {
    typedef vcT r_t; 
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Inf<vcT>())[0],  cT(nt2::Inf<T>()), 0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Minf<vcT>())[0],  cT(-1, nt2::Inf<T>()), 0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Mone<vcT>())[0],  cT(nt2::Mone<T>()), 0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Nan<vcT>())[0],  cT(nt2::Nan<T>()), 0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::One<vcT>())[0],  cT(nt2::Sqrt_2<T>()-nt2::One<T>()), 2);
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(vcT(nt2::Eps<vT>()))[0], cT(nt2::Eps<T>()*nt2::Half<T>()), 2);
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(vcT(nt2::Mone<vT>(),nt2::Two<vT>() ))[0], cT(0, 1), 2); 
    NT2_TEST_ULP_EQUAL(nt2::sqrt1pm1(nt2::Zero<vT>())[0],  cT(nt2::Zero<T>()), 0);
  } // end of test for floating_
}
