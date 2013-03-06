//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynom toolbox - roots/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/roots.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( roots_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::roots;
  using nt2::tag::roots_;
  typedef std::complex<T> cT;
  nt2::table<T> p =  nt2::_(T(1), T(3));
  p(2) = T(-3); p(3) = T(2);
  nt2::table<T> c = nt2::_(T(2), T(-1), T(1));
  NT2_DISPLAY(roots(p));
  NT2_DISPLAY(c);
  NT2_TEST(nt2::isulpequal(nt2::real(roots(p)), c, T(5.0)));
} // end of test for floating_






