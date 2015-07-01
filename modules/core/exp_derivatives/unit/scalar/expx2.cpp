//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/expx2.hpp>
#include <nt2/exp_derivatives/include/functions/expx2.hpp>
#include <nt2/include/functions/expx2.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/table.hpp>


#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/three.hpp>


NT2_TEST_CASE_TPL ( expx2,  NT2_REAL_TYPES)
{
  NT2_TEST_ULP_EQUAL(nt2::expx2(nt2::Half<T>()),
                     nt2::expx2<0>(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::expx2(nt2::Half<T>()),
                     nt2::expx2<1>(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::expx2(nt2::Half<T>())*nt2::Three<T>(),
                     nt2::expx2<2>(nt2::Half<T>())
                    , 0.5);


}


