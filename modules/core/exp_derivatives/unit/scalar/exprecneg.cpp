//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/exprecneg.hpp>
#include <nt2/exponential/include/functions/exprecneg.hpp>
#include <nt2/exp_derivatives/include/functions/exprecneg.hpp>
#include <nt2/exp_derivatives/include/functions/exprecneg.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( exprecneg,  NT2_REAL_TYPES)
{
  using nt2::exprecneg;

  NT2_TEST_ULP_EQUAL(nt2::exprecneg( boost::mpl::long_<0>(), nt2::Half<T>())
                    , nt2::exprecneg(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::exprecneg(boost::mpl::long_<1>(), nt2::Half<T>())
                    , nt2::exprecneg(nt2::Half<T>())/nt2::sqr(nt2::Half<T>())
                    ,0.5);
  NT2_TEST_ULP_EQUAL(nt2::exprecneg<1>(nt2::Half<T>())
                    , nt2::exprecneg(nt2::Half<T>())/nt2::sqr(nt2::Half<T>())
                    ,0.5);

  auto d2 =  [](const T& x) {return ((nt2::exprecneg(x))*(nt2::oneminus(x+x))/(nt2::sqr(nt2::sqr(x))));};

  NT2_TEST_ULP_EQUAL(nt2::exprecneg<2>(nt2::Half<T>())
                    , d2(nt2::Half<T>())
                    ,0.5);

  NT2_TEST_ULP_EQUAL(nt2::exprecneg( boost::mpl::long_<2>(),nt2::Half<T>())
                    , d2(nt2::Half<T>())
                    ,0.5);

}
