//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/wilkinson.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( wilkinson, NT2_REAL_TYPES)
{
  nt2::table<T> h7  = nt2::trans
    ( nt2::reshape( nt2::cons <T>(3,  1,  0,  0,  0,  0,  0,
                                  1,  2,  1,  0,  0,  0,  0,
                                  0,  1,  1,  1,  0,  0,  0,
                                  0,  0,  1,  0,  1,  0,  0,
                                  0,  0,  0,  1,  1,  1,  0,
                                  0,  0,  0,  0,  1,  2,  1,
                                  0,  0,  0,  0,  0,  1,  3
                                 )
                  , nt2::of_size(7, 7)
                  )
    );

  nt2::table<T> v = nt2::wilkinson(7, nt2::meta::as_<T>());
  nt2::table<T> d = nt2::wilkinson<T>(7);

  NT2_TEST_EQUAL(v, h7);
  NT2_TEST_EQUAL(d, h7);
}

NT2_TEST_CASE( wilkinson_untyped )
{
  typedef double T;

  nt2::table<T> h7  = nt2::trans
    ( nt2::reshape( nt2::cons<T>(3,  1,  0,  0,  0,  0,  0,
                                 1,  2,  1,  0,  0,  0,  0,
                                 0,  1,  1,  1,  0,  0,  0,
                                 0,  0,  1,  0,  1,  0,  0,
                                 0,  0,  0,  1,  1,  1,  0,
                                 0,  0,  0,  0,  1,  2,  1,
                                 0,  0,  0,  0,  0,  1,  3
                                )
                  , nt2::of_size(7, 7)
                  )
    );

  nt2::table<T> v = nt2::wilkinson(7);

  NT2_TEST_EQUAL(v, h7);
}
