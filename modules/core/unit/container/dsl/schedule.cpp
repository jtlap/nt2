/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container scheduler"

#include <nt2/table.hpp>
#include <nt2/include/functions/schedule.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/proto/debug.hpp>

template<class T, class N0>
struct node1 {};

template<class T, class N0, class N1>
struct node2 {};

template<class Tag, class Expr, int N>
struct as_node_impl;

template<class Expr>
struct as_node
 : as_node_impl< typename boost::proto::tag_of<Expr>::type
               , Expr
               , boost::proto::arity_of<Expr>::type::value
               >
{
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 0>
{
  typedef Tag type;
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 1>
{
  typedef node1<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
               > type;
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 2>
{
  typedef node2<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
               > type;
};

NT2_TEST_CASE( element_wise )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4;
  using nt2::schedule;

  NT2_TEST_EXPR_TYPE( schedule( a0 )
                    , as_node<_>
                    , boost::proto::tag::terminal
                    );

  NT2_TEST_EXPR_TYPE( schedule( assign(a0, a1) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( schedule( assign(a0, a1 + a2) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( schedule( assign(a0, nt2::plus(a1, a2)) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( schedule( assign(a0, a1 + a2 + a3) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( schedule( a0 + a1 )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  NT2_TEST_EXPR_TYPE( schedule( a0 + a1 + a2 )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
}

NT2_TEST_CASE( reduction )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4;
  using nt2::schedule;
  using nt2::sum;

#if 0
  NT2_TEST_EXPR_TYPE( schedule( sum(a0) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
#endif

#if 1
  NT2_TEST_EXPR_TYPE( schedule( assign(a0, sum(a1)) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );
#endif

#if 0
  NT2_TEST_EXPR_TYPE( schedule( a0 + sum(a1) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );

  NT2_TEST_EXPR_TYPE( schedule( assign(a0, a1 + sum(a2)) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );
#endif
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

  NT2_TEST_EXPR_TYPE( boost::mpl::identity< nt2::meta::call<nt2::tag::schedule_(table<T>&)>::type >()
                    , type
                    , table<T>&
                    );

#if 0
  NT2_TEST_EXPR_TYPE( schedule(a0(1))
                    , child0
                    , table<T>::parent&
                    );
#endif
}
