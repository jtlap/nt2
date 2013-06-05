//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - caurnd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/caurnd.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/options.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/meta/type_id.hpp>


NT2_TEST_CASE_TPL ( caurnd_real,  NT2_REAL_TYPES)
{

  using nt2::caurnd;
  using nt2::tag::caurnd_;
  // specific values tests
  nt2::table<T> b = caurnd(T(0.0), T(1.0));
  NT2_DISPLAY(b);
  nt2::table<T> c =  caurnd(T(0.0), T(1.0), 3);
  NT2_DISPLAY(c);
  nt2::table<T> d =  caurnd(T(0.0), T(1.0), 3, 5);
  NT2_DISPLAY(d);
  nt2::table<T> e =  caurnd(T(0.0), T(1.0), nt2::of_size(3, 2));
  NT2_DISPLAY(e);
  nt2::table<T> f =  caurnd(T(0.0), T(1.0), size(e));
  NT2_DISPLAY(f);
  NT2_TEST_COMPLETE("caurnd_real");
 } // end of test for floating_



