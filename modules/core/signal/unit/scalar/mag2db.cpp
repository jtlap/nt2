//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - mag2db/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/toolbox/signal/include/functions/mag2db.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>


NT2_TEST_CASE_TPL ( mag2db_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::mag2db;
  using nt2::tag::mag2db_;
  NT2_TEST_ULP_EQUAL(T(10)*log10(T(0.5)), mag2db(T(2), T(8)), 0.5);
  NT2_TEST_ULP_EQUAL(T(10)*log10(T(0.25)), mag2db(T(0.5)), 0.5);
} // end of test for floating_


