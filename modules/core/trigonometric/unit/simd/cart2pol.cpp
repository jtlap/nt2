//==============================================================================
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cart2pol.hpp>

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
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( cart2pol_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::cart2pol;
  using nt2::tag::cart2pol_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT x[] = {nt2::Zero<vT>(), nt2::One<vT>(), nt2::Two<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  size_t N =  sizeof(x)/sizeof(vT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<cart2pol_(vT, vT)>::type)
                  , (std::pair<vT,vT>)
                  );

  {
    vT r, t;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        cart2pol(x[i], x[j], r, t);
        NT2_TEST_EQUAL(r, nt2::hypot(x[i], x[j]));
        NT2_TEST_EQUAL(t, nt2::atan2(x[j], x[i]));
      }
    }
  }

  {
    vT r, t;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        r = cart2pol(x[i], x[j], t);
        NT2_TEST_EQUAL(r, nt2::hypot(x[i], x[j]));
        NT2_TEST_EQUAL(t, nt2::atan2(x[j], x[i]));
      }
    }
  }

  {
    vT r, t;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        boost::fusion::vector_tie(r, t) = cart2pol(x[i], x[j]);
        NT2_TEST_EQUAL(r, nt2::hypot(x[i], x[j]));
        NT2_TEST_EQUAL(t, nt2::atan2(x[j], x[i]));
      }
    }
  }

  {
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < N; ++j)
      {
        std::pair<vT,vT> p = cart2pol(x[i], x[j]);
        NT2_TEST_EQUAL(p.first,  nt2::hypot(x[i], x[j]));
        NT2_TEST_EQUAL(p.second, nt2::atan2(x[j], x[i]));
      }
    }
  }

}
