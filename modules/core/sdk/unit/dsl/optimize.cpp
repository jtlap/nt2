//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 container optimizer"

#include <nt2/table.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/optimize.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "as_node.hpp"

NT2_TEST_CASE( function )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2;

  NT2_TEST_EXPR_TYPE( nt2::optimize( a0(a1) )
                    , as_node<_>
                    , ( node2 < boost::proto::tag::function
                              , boost::proto::tag::terminal
                              , node4< nt2::tag::function_index_
                                     , node1 < nt2::tag::aggregate_
                                             , boost::proto::tag::terminal
                                             >
                                     , boost::simd::tag::box_
                                     , boost::simd::tag::box_
                                     , boost::simd::tag::box_
                                     >
                              >
                      )
                    )
}

NT2_TEST_CASE( fma )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2;

  NT2_TEST_EXPR_TYPE( nt2::optimize(a0 * a1 + a2 * a0)
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::multiplies
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( nt2::optimize(a0 * a1 + a2)
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( nt2::optimize(a0 + a1 * a2)
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( nt2::optimize(a0 * a1 + (a2 * a0 + a1))
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             , node3< nt2::tag::fma_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( nt2::optimize(a0 + a1 * (a2 * a0 + a1))
                    , as_node<_>
                    , ( node3< nt2::tag::fma_
                             , boost::proto::tag::terminal
                             , node3< nt2::tag::fma_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             , boost::proto::tag::terminal
                             >
                      )
                    );
}

struct child0
{
  template<class X>
  struct apply
   : boost::proto::result_of::child_c<X const&, 0>
  {
  };
};

struct type
{
  template<class X>
  struct apply
  {
    typedef typename X::type type;
  };
};

NT2_TEST_CASE( terminal_ref )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0;

  NT2_TEST_EXPR_TYPE( boost::mpl::identity< nt2::meta::call<nt2::tag::optimize_(table<T>&)>::type >()
                    , type
                    , table<T>&
                    );
}
