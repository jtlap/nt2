//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - polyvalm/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/polyvalm.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( polyvalm_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::polyvalm;
  using nt2::tag::polyvalm_;
  nt2::table<T> p =  nt2::_(T(1), T(4));
  nt2::table<T> a =  nt2::eye(3, nt2::meta::as_<T>());
  NT2_DISPLAY(polyvalm(p, a));
  NT2_TEST(nt2::isequal(polyvalm(p, a), T(10)*a));
  nt2::table<T> b = T(15)*nt2::eye(2, nt2::meta::as_<T>());
  b(2) = b(3) = T(11);
  nt2::table<T> c =  nt2::ones(2, nt2::meta::as_<T>());
  NT2_TEST(nt2::isequal(polyvalm(p, c), b));
  NT2_DISPLAY(polyvalm(p, c));
  NT2_DISPLAY(b);
} // end of test for floating_

