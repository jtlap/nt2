//==============================================================================
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/pol2cart.hpp>

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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( pol2cart_real__1_0,  NT2_SIMD_REAL_TYPES)
{

  using nt2::pol2cart;
  using nt2::tag::pol2cart_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  vT r[] = {nt2::Zero<vT>(), nt2::One<vT>(), nt2::Two<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  vT t[] = {nt2::Zero<vT>(), nt2::Pio_2<vT>(), nt2::Pio_3<vT>(), nt2::Pi<vT>(), nt2::Inf<vT>(), nt2::Minf<vT>(), nt2::Nan<vT>()};
  size_t N =  sizeof(r)/sizeof(vT);
  size_t M =  sizeof(t)/sizeof(vT);

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<pol2cart_(T, T)>::type)
                  , (std::pair<T,T>)
                  );

  {
    vT x, y;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < M; ++j)
      {
        pol2cart(r[i], t[j], x, y);
        NT2_TEST_ULP_EQUAL(x, r[i]*nt2::cos(t[j]), 3.5);
        NT2_TEST_ULP_EQUAL(y, r[i]*nt2::sin(t[j]), 3.5);
      }
    }
  }
  std::cout << "---------------------------------" << std::endl;
  {
    vT x, y;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < M; ++j)
      {
        x = pol2cart(r[i], t[j], y);
        NT2_TEST_ULP_EQUAL(x, r[i]*nt2::cos(t[j]), 3.5);
        NT2_TEST_ULP_EQUAL(y, r[i]*nt2::sin(t[j]), 3.5);
      }
    }
  }
  std::cout << "---------------------------------" << std::endl;

  {
    vT x, y;
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < M; ++j)
      {
        boost::fusion::vector_tie(x, y) = pol2cart(r[i], t[j]);
        NT2_TEST_ULP_EQUAL(x, r[i]*nt2::cos(t[j]), 3.5);
        NT2_TEST_ULP_EQUAL(y, r[i]*nt2::sin(t[j]), 3.5);
      }
    }
  }
  std::cout << "---------------------------------" << std::endl;

  {
    for(size_t i=0; i < N; ++i)
    {
      for(size_t j=0; j < M; ++j)
      {
        std::pair<vT,vT> p = pol2cart(r[i], t[j]);
        NT2_TEST_ULP_EQUAL(p.first,  r[i]*nt2::cos(t[j]), 3.5);
        NT2_TEST_ULP_EQUAL(p.second, r[i]*nt2::sin(t[j]), 3.5);
      }
    }
  }

}
