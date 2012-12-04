//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - caurnd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/caurnd.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/options.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/meta/type_id.hpp>
NT2_TEST_CASE_TPL ( caurnd_real__2_0,  NT2_REAL_TYPES)
{
//   std::cout << nt2::type_id(nt2::of_size(1)) <<  std::endl;
//   std::cout << nt2::type_id(nt2::of_size(1, 2)) <<  std::endl;
//   std::cout << nt2::type_id(nt2::of_size(1, 2, 3)) <<  std::endl;
//   std::cout << nt2::type_id(nt2::of_size(1, 2, 3, 4)) <<  std::endl;
//  nt2::table<T> a;
//  std::cout << nt2::type_id(nt2::size(a)) <<  std::endl;
//  std::cout << nt2::type_id(nt2::size(1.0)) <<  std::endl;
  using nt2::caurnd;
  using nt2::tag::caurnd_;
  // specific values tests
  nt2::table<T> a =  nt2::ones(3, 4, nt2::meta::as_<T>());
  nt2::table<T> b = caurnd(T(0.0), T(1.0));
  NT2_DISPLAY(b);
  b = caurnd(T(0.0), T(1.0));
  NT2_DISPLAY(b);
   nt2::table<T> m =  nt2::zeros(1, 3, nt2::meta::as_<T>());
   nt2::table<T> l =  nt2::ones(5, 1, nt2::meta::as_<T>());

  b = caurnd(m, l);
  NT2_DISPLAY(b);

  nt2::table<T> c =  caurnd(T(0.0), T(1.0), 3);
  NT2_DISPLAY(c);
  nt2::table<T> d =  caurnd(T(0.0), T(1.0), 3, 5);
  NT2_DISPLAY(d);
  nt2::table<T> e =caurnd(T(0.0), T(1.0), nt2::of_size(3, 2));
  NT2_DISPLAY(e);
//  nt2::table<T> f =  caurnd(T(0.0), T(1.0), size(e));
//   NT2_DISPLAY(f);
  {
    nt2::table<T> m =  nt2::zeros(1, 3, nt2::meta::as_<T>());
    nt2::table<T> l =  nt2::ones(5, 1, nt2::meta::as_<T>());
    NT2_DISPLAY(m);
    NT2_DISPLAY(l);

    nt2::table<T> g =  caurnd(m, l, 5, 3);
    NT2_DISPLAY(g);
    nt2::table<T> h =  caurnd(m, l);
    NT2_DISPLAY(h);
  }
 } // end of test for floating_


