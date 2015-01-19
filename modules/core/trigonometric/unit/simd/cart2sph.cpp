//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cart2sph.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( cart2sph_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::cart2sph;
  using nt2::tag::cart2sph_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT x[] = {nt2::Zero<vT>(), nt2::One<vT>(), nt2::Two<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  size_t N =  sizeof(x)/sizeof(vT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<cart2sph_(vT, vT, vT)>::type)
                  , (boost::fusion::tuple<vT,vT,vT>)
                  );

  {
    vT az,elev,r;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < N; ++k)
        {
          cart2sph(x[i], x[j], x[k], az, elev, r);
          NT2_TEST_ULP_EQUAL(az, nt2::atan2(x[j], x[i]), 3.5);
          NT2_TEST_ULP_EQUAL(elev, nt2::atan2(x[k], nt2::hypot(x[j], x[i])), 3.5);
          NT2_TEST_ULP_EQUAL(r, nt2::hypot(nt2::hypot(x[j], x[i]), x[k]), 3.5);
        }
      }
    }
  }

  {
    vT az,elev,r;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < N; ++k)
        {
          az =  cart2sph(x[i], x[j], x[k], elev, r);
          NT2_TEST_ULP_EQUAL(az, nt2::atan2(x[j], x[i]), 3.5);
          NT2_TEST_ULP_EQUAL(elev, nt2::atan2(x[k], nt2::hypot(x[j], x[i])), 3.5);
          NT2_TEST_ULP_EQUAL(r, nt2::hypot(nt2::hypot(x[j], x[i]), x[k]), 3.5);
        }
      }
    }
  }


  {
    vT az,elev,r;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < N; ++k)
        {
          boost::fusion::vector_tie(az,elev) = cart2sph(x[i], x[j], x[k], r);
          NT2_TEST_ULP_EQUAL(az, nt2::atan2(x[j], x[i]), 3.5);
          NT2_TEST_ULP_EQUAL(elev, nt2::atan2(x[k], nt2::hypot(x[j], x[i])), 3.5);
          NT2_TEST_ULP_EQUAL(r, nt2::hypot(nt2::hypot(x[j], x[i]), x[k]), 3.5);
        }
      }
    }
  }
  {
    vT az,elev,r;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < N; ++k)
        {
          boost::fusion::vector_tie(az,elev,r) =  cart2sph(x[i], x[j], x[k]);
          NT2_TEST_ULP_EQUAL(az, nt2::atan2(x[j], x[i]), 3.5);
          NT2_TEST_ULP_EQUAL(elev, nt2::atan2(x[k], nt2::hypot(x[j], x[i])), 3.5);
          NT2_TEST_ULP_EQUAL(r, nt2::hypot(nt2::hypot(x[j], x[i]), x[k]), 3.5);
        }
      }
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < N; ++k)
        {
          boost::fusion::tuple<vT,vT, vT> p = cart2sph(x[i], x[j], x[k]);
          NT2_TEST_ULP_EQUAL(boost::fusion::at_c<0>(p), nt2::atan2(x[j], x[i]), 3.5);
          NT2_TEST_ULP_EQUAL(boost::fusion::at_c<1>(p), nt2::atan2(x[k], nt2::hypot(x[j], x[i])), 3.5);
          NT2_TEST_ULP_EQUAL(boost::fusion::at_c<2>(p), nt2::hypot(nt2::hypot(x[j], x[i]), x[k]), 3.5);
        }
      }
    }
  }
}
