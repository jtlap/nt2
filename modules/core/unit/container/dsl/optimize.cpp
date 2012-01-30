/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container optimizer"

#include <nt2/table.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/optimize.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<class T, class N0, class N1>
struct node2 {};

template<class T, class N0, class N1, class N2>
struct node3 {};

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
struct as_node_impl<Tag, Expr, 2>
{
  typedef node2<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
               > type;
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 3>
{
  typedef node3<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 2>::type >::type
               > type;
};

NT2_TEST_CASE( function )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2;

  NT2_TEST_EXPR_TYPE( nt2::optimize( a0(a1) )
                    , as_node<_>
                    , ( node2< boost::proto::tag::function
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
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
   : boost::proto::result_of::child_c<X, 0>
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
  
  NT2_TEST_EXPR_TYPE( nt2::optimize(a0(1))
                    , child0
                    , table<T>::parent&
                    );
}
