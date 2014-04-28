//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/primes.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tic.hpp>
#include <nt2/include/functions/toc.hpp>

NT2_TEST_CASE_TPL ( primes_integer__1_0,  NT2_TYPES)
{

  using nt2::primes;
  using nt2::tag::primes_;

  T p[6] = {2, 3, 5, 7, 11, 13};
  nt2::table<T> myp = primes(T(15));
  // specific values tests
  NT2_DISPLAY(myp);
  for(size_t i=1; i <= 6; ++i)
  {
    NT2_TEST_EQUAL(p[i-1], myp(i));
  }
}
