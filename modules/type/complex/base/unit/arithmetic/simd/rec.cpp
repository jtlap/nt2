//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/rec.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>

NT2_TEST_CASE_TPL ( rec_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::rec;
  using nt2::tag::rec_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Inf<T>(),  nt2::Inf<T>() ))), nt2::splat<vcT>(cT(nt2::Zero<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Minf<T>(), nt2::Minf<T>()))), nt2::splat<vcT>(cT(nt2::Zero<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Inf<T>(),  nt2::Zero<T>()))), nt2::splat<vcT>(cT(nt2::Zero<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Inf<T>( )))), nt2::splat<vcT>(cT(nt2::Zero<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Minf<T>(), nt2::Zero<T>()))), nt2::splat<vcT>(cT(nt2::Zero<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Minf<T>()))), nt2::splat<vcT>(cT(nt2::Zero<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Zero<T>()))), nt2::splat<vcT>(cT(nt2::Inf<cT>() )));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Mzero<T>(),nt2::Zero<T>()))), nt2::splat<vcT>(cT(nt2::Minf<cT>())));
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Nan<T>(),  nt2::Nan<T>() ))), nt2::Cnan<vcT>());
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Nan<T>(),  nt2::One<T>() ))), nt2::Cnan<vcT>());
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::One<T>(),  nt2::Nan<T>() ))), nt2::Cnan<vcT>());
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Nan<T>(),  nt2::Zero<T>()))), nt2::Nan<vcT>());
   NT2_TEST_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Nan<T>() ))), nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Nan<T>())));
#endif
   NT2_TEST_EQUAL(nt2::rec(nt2::One<vcT>()), nt2::One<vcT>());
   NT2_TEST_EQUAL(nt2::rec(nt2::One<vdT>()), nt2::One<vdT>());

   NT2_TEST_ULP_EQUAL(nt2::rec(nt2::splat<vcT>(cT(nt2::One<T>(), nt2::One<T>() ))),
                      nt2::splat<vcT>(cT(nt2::Half<T>(),nt2::Mhalf<T>())), 0.5);

}
