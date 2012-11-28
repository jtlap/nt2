//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - polysub/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/polysub.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>

#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( polysub_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::polysub;
  using nt2::tag::polysub_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(4));
  nt2::table<T, nt2::_2D> b =  nt2::_(T(1), T(2));
  nt2::table<T, nt2::_2D> c;
  T aab[] = { 1, 2, 2, 2};
  nt2::table<T> d(nt2::of_size(1, 4), &aab[0], &aab[4]);
  c = polysub(a, b);

  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(c);
  NT2_DISPLAY(polysub(a, b));
  NT2_DISPLAY(polysub(b, a));
  NT2_TEST(nt2::isequal(d,polysub(a, b)));
  NT2_TEST(nt2::isequal(-d,polysub(b, a)));
} // end of test for floating_


