//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_UNIT_DSL_GENERATOR_AS_NODE_INCLUDED
#define NT2_UNIT_DSL_GENERATOR_AS_NODE_INCLUDED

template<class T, class N0>
struct node1 {};

template<class T, class N0, class N1>
struct node2 {};

template<class T, class N0, class N1, class N2>
struct node3 {};

template<class T, class N0, class N1, class N2, class N3>
struct node4 {};

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

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 3>
{
  typedef node3<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 2>::type >::type
               > type;
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 4>
{
  typedef node4<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 2>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 3>::type >::type
               > type;
};

#endif
