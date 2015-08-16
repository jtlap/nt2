//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/sized_mk.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cat.hpp>
#include <boost/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>



NT2_TEST_CASE_TPL( sized_mk, NT2_TYPES )
{
  using nt2::table;
  using nt2::sized_mk;
  table<T> ref  =  nt2::cons<T>(nt2::of_size(4, 2)
                               , T(1.), T(3.)
                               , T(5.), T(7.)
                               , T(2.), T(4.)
                               , T(6.), T(8.)
                               );

  NT2_TEST_EQUAL( ref, sized_mk ( nt2::of_size(4, 2)
                                , T(1.), T(2.)
                                , T(3.), T(4.)
                                , T(5.), T(6.)
                                , T(7.), T(8.)
                            )
                );
  table<T> ref1  = nt2::cat(3,
                            nt2::cons<T>(nt2::of_size(2, 2)
                                        , T(1.), T(3.)
                                        , T(2.), T(4.)),
                            nt2::cons<T>(nt2::of_size(2, 2)
                                        , T(5.), T(7.)
                                        , T(6.), T(8.))
                           );

  NT2_TEST_EQUAL( ref1, sized_mk ( nt2::of_size(2, 2, 2)
                                , T(1.), T(2.)
                                , T(3.), T(4.)
                                , T(5.), T(6.)
                                , T(7.), T(8.)
                            )
                );
  NT2_TEST_EQUAL( ref1, sized_mk<T>( nt2::of_size(2, 2, 2),
                                    1, 2
                                  , 3, 4
                                  , 5, 6
                                  , 7, 8
                            )
                );
  NT2_TEST_EQUAL(sized_mk<T>( nt2::of_size(2, 1), 1, 2),
                 nt2::cons<T>( nt2::of_size(2, 1),1, 2));
  NT2_TEST_EQUAL(sized_mk<T>( nt2::of_size(1, 2), 1, 2),
              nt2::cons<T>( nt2::of_size(2, 1),1, 2));

  NT2_TEST_ASSERT(sized_mk<T>( nt2::of_size(2, 1), 1, 2, 3));
  NT2_TEST_ASSERT(sized_mk<T>( nt2::of_size(2, 1), 1));
}
