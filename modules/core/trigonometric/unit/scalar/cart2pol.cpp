//==============================================================================
//         Copyright 2015 J.T. Lapreste
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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( cart2pol_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::cart2pol;
  using nt2::tag::cart2pol_;
  T x[] = {nt2::Zero<T>(), nt2::One<T>(), nt2::Two<T>(), nt2::Inf<T>(), nt2::Minf<T>(), nt2::Nan<T>()};
  size_t N =  sizeof(x)/sizeof(T);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<cart2pol_(T, T)>::type)
                  , (std::pair<T,T>)
                  );

  {
    T r, t;
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
    T r, t;
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
    T r, t;
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
        std::pair<T,T> p = cart2pol(x[i], x[j]);
        NT2_TEST_EQUAL(p.first,  nt2::hypot(x[i], x[j]));
        NT2_TEST_EQUAL(p.second, nt2::atan2(x[j], x[i]));
      }
    }
  }

}
