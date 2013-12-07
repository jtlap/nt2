//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/reduction/include/functions/dot.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

NT2_TEST_CASE_TPL (dot_cplx, NT2_SIMD_REAL_TYPES)
{
  using nt2::dot;
  using nt2::tag::dot_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>               cT;
  typedef native<T,ext_t>               vT;
  typedef native<cT,ext_t>              vcT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<dot_(vcT, vcT)>::type
                  , cT
                  );
  vcT a[] = {nt2::Zero<vcT>(), nt2::One<vcT>(), nt2::I<vcT>(), nt2::Pi<vcT>(),
             nt2::Pio_2<vcT>(), nt2::Inf<vcT>(), nt2::Minf<vcT>(), nt2::Nan<vcT>(),
             vcT(nt2::Zero<vT>(),nt2::Zero<vT>()),vcT(nt2::Inf<vT>(),nt2::Zero<vT>()),
             vcT(nt2::Minf<vT>(),nt2::Zero<vT>()),vcT(nt2::Nan<vT>(),nt2::Zero<vT>()),
             vcT(nt2::Zero<vT>(),nt2::Inf<vT>()), vcT(nt2::Inf<vT>(),nt2::Inf<vT>()),
             vcT(nt2::Minf<vT>(),nt2::Inf<vT>()), vcT(nt2::Nan<vT>(),nt2::Inf<vT>()),
             vcT(nt2::Zero<vT>(),nt2::Minf<vT>()),vcT(nt2::Inf<vT>(),nt2::Minf<vT>()),
             vcT(nt2::Minf<vT>(),nt2::Minf<vT>()),vcT(nt2::Nan<vT>(),nt2::Minf<vT>()),
             vcT(nt2::Zero<vT>(),nt2::Nan<vT>()), vcT(nt2::Inf<vT>(),nt2::Nan<vT>()),
             vcT(nt2::Minf<vT>(),nt2::Nan<vT>()), vcT(nt2::Nan<vT>(),nt2::Nan<vT>()),
             vcT(nt2::Zero<vT>(),nt2::Pi <vT>()), vcT(nt2::Inf<vT>(),nt2::Pi <vT>()),
             vcT(nt2::Minf<vT>(),nt2::Pi <vT>()), vcT(nt2::Nan<vT>(),nt2::Pi <vT>()),
  };
  size_t N =  sizeof(a)/sizeof(vcT);
  for(size_t i=0; i < N; i++)
  {
    vcT a1 = a[i];
    cT aa1 = nt2::extract<0>(a1);
    for(size_t j=0; j < N; j++)
    {
      vcT a2 = a[j];
      cT aa2 = nt2::extract<0>(a2);
      NT2_TEST_ULP_EQUAL(nt2::dot(a1, a2),nt2::multiplies(nt2::dot(aa1, aa2), T(nt2::meta::cardinal_of<vcT>::value)), 0.5);
    }
  }
}
