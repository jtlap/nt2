//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cosine.hpp>
#include <nt2/trig_derivatives/include/functions/cosine.hpp>
#include <nt2/include/functions/cosine.hpp>
#include <nt2/include/functions/sine.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_3.hpp>


NT2_TEST_CASE_TPL ( cosine,  NT2_REAL_TYPES)
{
  using nt2::cosine;
  using nt2::sine;



//   T l = cosine<nt2::medium_,1>(nt2::Pio_3<T>());
// //  T l = cosine<nt2::medium_>(boost::mpl::long_<1>(), nt2::Pio_3<T>());
//   T r = (-sine<nt2::medium_>(nt2::Pio_3<T>()));
//   NT2_TEST_ULP_EQUAL(l, r, 1.5);
  NT2_TEST_ULP_EQUAL((cosine<nt2::medium_,1>(nt2::Pio_3<T>())),
                     (-sine<nt2::medium_>(nt2::Pio_3<T>())), 1.5);
  NT2_TEST_ULP_EQUAL((cosine<nt2::medium_,2>(nt2::Pio_3<T>())),
                     (-cosine<nt2::medium_>(nt2::Pio_3<T>())), 1.5);
  NT2_TEST_ULP_EQUAL((cosine<nt2::medium_,3>(nt2::Pio_3<T>())),
                     sine<nt2::medium_>(nt2::Pio_3<T>()), 1.5);

}

