//==============================================================================
//         Copyright 2015  J.T. Lapreste
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/kron.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>



NT2_TEST_CASE_TPL( kron, NT2_TYPES )
{
  using nt2::_;
  using nt2::kron;

  nt2::table<T> a = nt2::reshape(_(T(1), T(6)), 2, 3);
  nt2::table<T> b = nt2::reshape(_(T(1), T(4)), 2, 2);
  nt2::table<T> c = kron(a, b);
  nt2::table<T> rc = nt2::cons<T>(nt2::of_size(4, 6),
                             1,     2,     2,     4,
                             3,     4,     6,     8,
                             3,     6,     4,     8,
                             9,    12,    12,    16,
                             5,    10,     6,    12,
                             15,   20,   18,    24);

  NT2_TEST_EQUAL(kron(T(3), T(2)), T(6));
  NT2_TEST_EQUAL(kron(a, T(2)), T(2)*a);
  NT2_TEST_EQUAL(kron(T(2), a), T(2)*a);
  NT2_TEST_EQUAL(c,rc);
}

