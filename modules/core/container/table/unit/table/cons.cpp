//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <boost/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<typename Expr> void inline check_properties(Expr const& )
{
  using nt2::meta::option;
  typedef typename option<Expr,nt2::tag::storage_duration_>::type sd_t;
  NT2_TEST_TYPE_IS( typename sd_t::storage_duration_type, nt2::automatic_ );
}

NT2_TEST_CASE_TPL( cons, NT2_TYPES )
{
  using nt2::table;
  using nt2::cons;

  boost::array<T, 8> ref  = {{  T(1.), T(2.), T(3.), T(4.)
                              , T(5.), T(6.), T(7.), T(8.)
                            }};

  NT2_TEST_EQUAL( ref, cons ( T(1.), T(2.), T(3.), T(4.)
                            , T(5.), T(6.), T(7.), T(8.)
                            )
                );

  check_properties( cons( T(1.), T(2.), T(3.), T(4.)
                        , T(5.), T(6.), T(7.), T(8.)
                        )
                  );
}

NT2_TEST_CASE_TPL( sized_cons, NT2_TYPES )
{
  using nt2::table;
  using nt2::cons;
  using nt2::of_size;

  boost::array<T, 8> ref  = {{  T(1.), T(2.), T(3.), T(4.)
                              , T(5.), T(6.), T(7.), T(8.)
                            }};

  NT2_TEST_EQUAL( ref, cons ( of_size(4,2)
                            , T(1.), T(2.), T(3.), T(4.)
                            , T(5.), T(6.), T(7.), T(8.)
                            )
                );

  check_properties( cons( of_size(4,2)
                        , T(1.), T(2.), T(3.), T(4.)
                        , T(5.), T(6.), T(7.), T(8.)
                        )
                  );

  NT2_TEST_ASSERT ( cons ( of_size(5,3)
                        , T(1.), T(2.), T(3.), T(4.)
                        , T(5.), T(6.), T(7.), T(8.)
                        )
                  );
}
