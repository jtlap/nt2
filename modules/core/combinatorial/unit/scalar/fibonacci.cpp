//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - fibonacci/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
///
#include <nt2/combinatorial/include/functions/fibonacci.hpp>
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
#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( fibonacci_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::fibonacci;
  using nt2::tag::fibonacci_;

  // specific values tests
  NT2_TEST_EQUAL(fibonacci(T(1),T(1), 10), T(55));
} // end of test for floating_

NT2_TEST_CASE_TPL ( fibonacci_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::fibonacci;
  using nt2::tag::fibonacci_;
  typedef typename nt2::meta::as_integer<T>::type i_type;
  nt2::table<T> res =  nt2::cons<T>(nt2::of_size(1, 10), T(1),T(1),T(2),T(3),T(5),T(8),T(13),T(21),T(34),T(55));
  nt2::table<T> fib = fibonacci(T(1), T(1), nt2::_(1, 10));
  NT2_TEST_EQUAL(fib, res);
 } // end of test for integer_



