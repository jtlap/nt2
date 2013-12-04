//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sincos.hpp>

#include <nt2/include/constants/pio2_3.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( sincos, NT2_REAL_TYPES)
{

  using nt2::sincos;
  using nt2::tag::sincos_;
  typedef typename std::complex<T> cT;
  cT a[] = {nt2::Zero<cT>(), nt2::One<cT>(), nt2::Pio2_3<cT>(), nt2::Pi<cT>(),
            nt2::Pio_2<cT>(), nt2::Inf<cT>(), nt2::Minf<cT>(), nt2::Nan<cT>(),
            cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
            cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
            cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
            cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
            cT(nt2::Zero<T>(),nt2::Pi <T>()), cT(nt2::Inf<T>(),nt2::Pi <T>()), cT(nt2::Minf<T>(),nt2::Pi <T>()), cT(nt2::Nan<T>(),nt2::Pi <T>())};
  size_t N =  sizeof(a)/sizeof(cT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<sincos_(cT)>::type)
                  , (std::pair<cT,cT>)
                  );

  {
    cT s, c;
    for(size_t i=0; i < N; ++i)
    {
      sincos(a[i], s, c);
      NT2_TEST_EQUAL(s, nt2::sin(a[i]));
      NT2_TEST_EQUAL(c, nt2::cos(a[i]));
    }
  }

  {
    cT s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = sincos(a[i], c);
      NT2_TEST_EQUAL(s, nt2::sin(a[i]));
      NT2_TEST_EQUAL(c, nt2::cos(a[i]));
    }
  }

  {
    cT s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = sincos(a[i]);
      NT2_TEST_EQUAL(s, nt2::sin(a[i]));
      NT2_TEST_EQUAL(c, nt2::cos(a[i]));
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<cT,cT> p = sincos(a[i]);
      NT2_TEST_EQUAL(p.first,  nt2::sin(a[i]));
      NT2_TEST_EQUAL(p.second, nt2::cos(a[i]));
    }
  }

}
