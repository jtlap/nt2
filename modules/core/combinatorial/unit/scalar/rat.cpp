//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - rat/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
///
#include <nt2/toolbox/combinatorial/include/functions/rat.hpp>
#include <nt2/include/functions/ulpdist.hpp>
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
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rat_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::rat;
  using nt2::tag::rat_;

  // specific values tests
  T n, d;
  rat(T(1.5), n, d);
  std::cout << "n " << n << " d " <<  d <<  std::endl;
  NT2_TEST_ULP_EQUAL(n, T(3), 0);
  NT2_TEST_ULP_EQUAL(d, T(2), 0);
  rat(T(3.14159), n, d);
  std::cout << "n " << n << " d " <<  d <<  std::endl;
  NT2_TEST_ULP_EQUAL(n, T(355), 0);
  NT2_TEST_ULP_EQUAL(d, T(113), 0);
} // end of test for floating_

