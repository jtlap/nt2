//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/minus.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( minus_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::minus;
  using nt2::tag::minus_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
    NT2_TEST_EQUAL(nt2::minus(vcT(nt2::Inf<vT>(), nt2::Zero<vT>()), vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), vcT(nt2::Nan<vT>(), nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::Inf<vdT>()),  vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), vcT(nt2::Nan<vT>(), nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::Inf<vdT>()),   vdT(nt2::Inf<vdT>())),  vdT(nt2::Nan<vdT>() ));
#endif
    NT2_TEST_EQUAL(nt2::minus(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::One<vT>(),nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vcT(nt2::Zero<vT>(),nt2::Zero<vT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vcT(nt2::Zero<vT>(),nt2::One<vT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>())), vcT(nt2::Mone<vT>(),nt2::One<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vcT(nt2::One<vT>(), nt2::Zero<vT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>())), vcT(nt2::Zero<vT>(), nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::One<vdT>()),  vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::One<vT>(),nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::Zero<vdT>()), vcT(nt2::Zero<vT>(),nt2::Zero<vT>())), vcT(nt2::Zero<vT>(),nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::Zero<vdT>()), vcT(nt2::One<vT>(), nt2::Zero<vT>())), vcT(nt2::Mone<vT>(),nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::One<vdT>()),  vcT(nt2::One<vT>(), nt2::Zero<vT>())), vcT(nt2::Zero<vT>(), nt2::Zero<vT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::One<vdT>()),   vdT(nt2::Zero<vdT>())), vdT(nt2::One<vdT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::Zero<vdT>()),  vdT(nt2::Zero<vdT>())), vdT(nt2::Zero<vdT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::Zero<vdT>()),  vdT(nt2::One<vdT>())),  vdT(nt2::Mone<vdT>()));
    NT2_TEST_EQUAL(nt2::minus(vdT(nt2::One<vdT>()),   vdT(nt2::One<vdT>())),  vdT(nt2::Zero<vdT>() ));
}
