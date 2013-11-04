//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/elliptic/include/functions/scalar/ellipke.hpp>
#include <nt2/elliptic/include/functions/simd/ellipke.hpp>

#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/eps.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( ellipke_real,  NT2_SIMD_REAL_TYPES)
{

  using nt2::ellipke;
  using nt2::tag::ellipke_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT a[] = {nt2::One<vT>(), nt2::Zero<vT>(), nt2::Half<vT>(), nt2::Two<vT>()};
  size_t N =  sizeof(a)/sizeof(vT);
  vT e1[] = {nt2::Inf<vT>(), nt2::Pio_2<vT>(), nt2::splat<vT>(1.854074677301372), nt2::Nan<vT>()};
  vT e2[] = {nt2::One<vT>(), nt2::Pio_2<vT>(), nt2::splat<vT>(1.350643881047675), nt2::Nan<vT>()};

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<ellipke_(vT)>::type)
                  , (std::pair<vT,vT>)
                  );
  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<ellipke_(vT, T)>::type)
                  , (std::pair<vT,vT>)
                  );
  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<ellipke_(vT, T, vT&)>::type)
                  , (vT)
                  );
  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<ellipke_(vT, T, vT&, vT&)>::type)
                  , (void)
                  );

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      ellipke(a[i],nt2::Eps<T>(), s, c);
      NT2_TEST_ULP_EQUAL(s, e1[i], 1);
      NT2_TEST_ULP_EQUAL(c, e2[i], 1);
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      s = ellipke(a[i], nt2::Eps<T>(), c);
      NT2_TEST_ULP_EQUAL(s, e1[i], 1);
      NT2_TEST_ULP_EQUAL(c, e2[i], 1);
    }
  }

  {
    vT s, c;
    for(size_t i=0; i < N; ++i)
    {
      boost::fusion::vector_tie(s, c) = ellipke(a[i]);
      NT2_TEST_ULP_EQUAL(s, e1[i], 1);
      NT2_TEST_ULP_EQUAL(c, e2[i], 1);
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      std::pair<vT,vT> p = ellipke(a[i]);
      NT2_TEST_ULP_EQUAL(p.first,  e1[i], 1);
      NT2_TEST_ULP_EQUAL(p.second, e2[i], 1);
    }
  }
}
