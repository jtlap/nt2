//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 integration toolbox - quasi"
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/include/functions/quasi.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>

NT2_TEST_CASE_TPL( quasi_real_out, NT2_REAL_TYPES )
{
  using nt2::quasi;
  typedef nt2::table<T> tab_t;

  tab_t xx
    = nt2::trans(nt2::cons(nt2::of_size(10, 3),
                           T(0.5) ,T(0.25) ,T(0.75) ,T(0.375) ,T(0.875) ,T(0.125) ,T(0.625) ,T(0.3125) ,T(0.8125) ,T(0.0625)
                          ,T(0.5) ,T(0.75) ,T(0.25) ,T(0.625) ,T(0.125) ,T(0.375) ,T(0.875) ,T(0.3125) ,T(0.8125) ,T(0.5625)
                          ,T(0.5) ,T(0.25) ,T(0.75) ,T(0.125) ,T(0.625) ,T(0.375) ,T(0.875) ,T(0.6875) ,T(0.1875) ,T(0.9375)
                          ));
  tab_t xx1
    = nt2::trans(nt2::cons(nt2::of_size(10, 3),
                           T(0.6875) ,T(0.1875) ,T(0.9375) ,T(0.4375) ,T(0.96875) ,T(0.46875) ,T(0.71875) ,T(0.21875) ,T(0.59375) ,T(0.09375)
                          ,T(0.4375) ,T(0.9375) ,T(0.6875) ,T(0.1875) ,T(0.34375) ,T(0.84375) ,T(0.59375) ,T(0.09375) ,T(0.96875) ,T(0.46875)
                          ,T(0.0625) ,T(0.5625) ,T(0.3125) ,T(0.8125) ,T(0.90625) ,T(0.40625) ,T(0.65625) ,T(0.15625) ,T(0.78125) ,T(0.28125)
                          ));
  tab_t x =  quasi(3, 10, nt2::meta::as_<T>());
  NT2_TEST_EQUAL(xx, x);
  tab_t x1 =  quasi(3, 10, nt2::meta::as_<T>());
  NT2_TEST_EQUAL(xx1, x1);
}
