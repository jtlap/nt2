//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - polyint/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/polyder.hpp>
#include <nt2/include/functions/polyint.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>

#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( polyint_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::polyint;
  using nt2::tag::polyint_;
  nt2::table<T> a =  nt2::_(T(4), T(-1), T(1));
  nt2::table<T> c(nt2::of_size(1, 0));
  NT2_DISPLAY(polyint(a, T(1)));
  nt2::table<T> ia =  polyint(a, T(1));
  NT2_DISPLAY(polyint(c, T(1)));
  NT2_TEST(nt2::isequal(ia, nt2::ones(1,5, nt2::meta::as_<T>())));
} // end of test for floating_


