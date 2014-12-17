//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cos.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <complex>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( cos, NT2_SIMD_REAL_TYPES)
{

  using nt2::cos;
  using nt2::tag::cos_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                cT;
  typedef native<cT,ext_t>              vcT;
  typedef typename nt2::meta::call<cos_(vcT)>::type r_t;

  NT2_TEST_TYPE_IS(r_t,vcT);

  cT a[] = {nt2::Zero<cT>(), nt2::One<cT>(), nt2::Pio2_3<cT>(), nt2::Pi<cT>(),
            nt2::Pio_2<cT>(), nt2::Inf<cT>(), nt2::Minf<cT>(), nt2::Nan<cT>(),
            cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
            cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
            cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
            cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
            cT(nt2::Zero<T>(),nt2::Pi <T>()), cT(nt2::Inf<T>(),nt2::Pi <T>()), cT(nt2::Minf<T>(),nt2::Pi <T>()), cT(nt2::Nan<T>(),nt2::Pi <T>()),
            cT(0.5, -0.5), cT(1, 1), cT(1, 10), cT(10, 10), cT(10, 1), nt2::Mzero<cT>()
          };
  size_t N =  sizeof(a)/sizeof(cT);
  for(size_t i=0; i < N; ++i)
  {
    NT2_TEST_ULP_EQUAL(nt2::cos(nt2::splat<vcT>(a[i])), nt2::splat<vcT>(nt2::cos(a[i])), 1.0);
  }

}

