//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exp_derivatives/include/functions/nthroot.hpp>
#include <nt2/exp_derivatives/include/functions/cbrt.hpp>
#include <nt2/include/functions/nthroot.hpp>
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

// template <class Tag, long N, class X >  BOOST_FORCEINLINE
// auto  d(const X& x)
//   -> decltype(nt2::functor<Tag>()(/*boost::mpl::long_<N>(),*/ x))
// {
//   return nt2::functor<Tag>()(/*boost::mpl::long_<N>(),*/ x);
// }

NT2_TEST_CASE_TPL ( nthroot,  NT2_REAL_TYPES)
{

  NT2_TEST_ULP_EQUAL(nt2::nthroot<0>(nt2::Half<T>(), 3)
                    , nt2::nthroot(nt2::Half<T>(), 3)
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::nthroot<1>(nt2::Half<T>(), 3)
                    , nt2::cbrt<1>(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::nthroot<2>(nt2::Half<T>(), 3)
                    , nt2::cbrt<2>(nt2::Half<T>())
                    , 0.5);

}


