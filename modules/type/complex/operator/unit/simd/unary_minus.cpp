//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - arg/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
///

#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/simd/include/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

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

  // specific values tests
  {
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::splat<vcT>(cT(T(1.1),T(1.6))))[0], cT(T(-1.1),T(-1.6)));
  }
  {
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Inf<vcT>())[0], nt2::Minf<vcT>()[0]);
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Minf<vcT>())[0], nt2::Inf<vcT>()[0]);
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Mone<vcT>())[0], nt2::One<vcT>()[0]);
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Nan<vcT>())[0], nt2::Nan<vcT>()[0]);
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::One<vcT>())[0], nt2::Mone<vcT>()[0]);
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Zero<vcT>())[0], nt2::Zero<vcT>()[0]);
  }
  {
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::splat<vciT>(ciT(T(-1.1))))[0], ciT(T( 1.1)) );
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::splat<vciT>(ciT(T(1.1))))[0],ciT(T(-1.1)));
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Inf<vciT>())[0], nt2::Minf<ciT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Minf<vciT>())[0],nt2::Inf<ciT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Mone<vciT>())[0],nt2::One<ciT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Nan<vciT>())[0], nt2::Nan<ciT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::One<vciT>())[0], nt2::Mone<ciT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Zero<vciT>())[0], nt2::Zero<ciT>());
  }
  {
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::splat<vdT>(dT(T(-1.1))))[0], dT(T(1.1)));
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::splat<vdT>(dT(T(1.1))))[0],  dT(T(-1.1)));
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Inf<vdT>())[0], nt2::Minf<dT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Minf<vdT>())[0], nt2::Inf<dT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Mone<vdT>())[0], nt2::One<dT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Nan<vdT>())[0], nt2::Nan<dT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::One<vdT>())[0], nt2::Mone<dT>());
    NT2_TEST_EQUAL(nt2::unary_minus(nt2::Zero<vdT>())[0], nt2::Zero<dT>());
  }
} // end of test for floating_
