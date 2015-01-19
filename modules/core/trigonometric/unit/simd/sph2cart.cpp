//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sph2cart.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_3.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/mpl/at.hpp>

NT2_TEST_CASE_TPL ( sph2cart_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::sph2cart;
  using nt2::tag::sph2cart_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  vT r[] = {nt2::Zero<vT>(), nt2::One<vT>(), nt2::Two<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  vT t[] = {nt2::Zero<vT>(), nt2::Pio_2<vT>(), nt2::Pio_3<vT>(), nt2::Pi<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  size_t M =  sizeof(r)/sizeof(vT);
  size_t N =  sizeof(t)/sizeof(vT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<sph2cart_(vT, vT, vT)>::type)
                  , (boost::fusion::tuple<vT,vT,vT>)
                  );

  {
    vT x, y, z;
    for(size_t i=0; i < N; ++i)  // az
    {
      for(size_t j=0; j < N; ++j) // elev
      {
        for(size_t k=0; k < M; ++k) // r
        {
          sph2cart(t[i], t[j], r[k], x, y, z);
          NT2_TEST_ULP_EQUAL(x, r[k]*nt2::cos(t[j])*nt2::cos(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(y, r[k]*nt2::cos(t[j])*nt2::sin(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(z, r[k]*nt2::sin(t[j]), 3.5);
        }
      }
    }
  }
  std::cout << "---------------------------------" << std::endl;
  {
    vT x, y, z;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < M; ++k) // r
        {
          x = sph2cart(t[i], t[j], r[k], y, z);
          NT2_TEST_ULP_EQUAL(x, r[k]*nt2::cos(t[j])*nt2::cos(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(y, r[k]*nt2::cos(t[j])*nt2::sin(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(z, r[k]*nt2::sin(t[j]), 3.5);
        }
      }
    }
 }
  std::cout << "---------------------------------" << std::endl;

  {
    vT x, y, z;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < M; ++k) // r
        {
          boost::fusion::vector_tie(x, y) = sph2cart(t[i], t[j], r[k], z);
          NT2_TEST_ULP_EQUAL(x, r[k]*nt2::cos(t[j])*nt2::cos(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(y, r[k]*nt2::cos(t[j])*nt2::sin(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(z, r[k]*nt2::sin(t[j]), 3.5);
        }
      }
    }
  }
  std::cout << "---------------------------------" << std::endl;
  {
    vT x, y, z;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < M; ++k) // r
        {
          boost::fusion::vector_tie(x, y, z) = sph2cart(t[i], t[j], r[k]);
          NT2_TEST_ULP_EQUAL(x, r[k]*nt2::cos(t[j])*nt2::cos(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(y, r[k]*nt2::cos(t[j])*nt2::sin(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(z, r[k]*nt2::sin(t[j]), 3.5);
        }
      }
    }
  }
  std::cout << "---------------------------------" << std::endl;

  {
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        for(size_t k=0; k < M; ++k) // r
        {
          boost::fusion::tuple<vT,vT,vT> p = sph2cart(t[i], t[j], r[k]);
          NT2_TEST_ULP_EQUAL(boost::fusion::at_c<0>(p), r[k]*nt2::cos(t[j])*nt2::cos(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(boost::fusion::at_c<1>(p), r[k]*nt2::cos(t[j])*nt2::sin(t[i]), 3.5);
          NT2_TEST_ULP_EQUAL(boost::fusion::at_c<2>(p), r[k]*nt2::sin(t[j]), 3.5);
        }
      }
    }
  }

}
