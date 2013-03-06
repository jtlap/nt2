//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - conj/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/arithmetic/include/functions/conj.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

NT2_TEST_CASE_TPL ( conj_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
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
  {
    NT2_TEST_EQUAL( nt2::conj(nt2::splat<vcT>( cT( T(-1.1), T(-1.6) ) ))[0]
                  , cT( T(-1.1), T( 1.6))
                  );

    NT2_TEST_EQUAL( nt2::conj(nt2::splat<vcT>( cT( T( 1.1), T( 1.6) ) ))[0]
                  , cT( T( 1.1), T(-1.6))
                  );
  }
  {
    NT2_TEST_EQUAL(nt2::conj(nt2::Inf<vcT>())[0], nt2::Inf<cT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Minf<vcT>())[0], nt2::Minf<cT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Mone<vcT>())[0], nt2::Mone<cT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Nan<vcT>())[0], nt2::Nan<cT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::One<vcT>())[0], nt2::One<cT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Zero<vcT>())[0], nt2::Zero<cT>());
  }
  {
    NT2_TEST_EQUAL(nt2::conj(nt2::splat<vciT>(ciT(-1)))[0], nt2::One<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::splat<vciT>(ciT(1)))[0], nt2::Mone<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::Inf<vciT>())[0], nt2::Minf<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::Minf<vciT>())[0], nt2::Inf<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::Mone<vciT>())[0], nt2::One<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::Nan<vciT>())[0], nt2::Nan<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::One<vciT>())[0], nt2::Mone<vciT>()[0]);
    NT2_TEST_EQUAL(nt2::conj(nt2::Zero<vciT>())[0], nt2::Zero<vciT>()[0]);
  }
  {
    NT2_TEST_EQUAL(nt2::conj(nt2::splat<vdT>(dT(-1)))[0], nt2::Mone<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::splat<vdT>(dT(1)))[0], nt2::One<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Inf<vdT>())[0], nt2::Inf<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Minf<vdT>())[0], nt2::Minf<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Mone<vdT>())[0], nt2::Mone<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Nan<vdT>())[0], nt2::Nan<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::One<vdT>())[0], nt2::One<dT>());
    NT2_TEST_EQUAL(nt2::conj(nt2::Zero<vdT>())[0], nt2::Zero<dT>());
  }
}
