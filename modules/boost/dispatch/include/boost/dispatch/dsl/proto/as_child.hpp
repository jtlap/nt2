/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_DSL_PROTO_AS_CHILD_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_PROTO_AS_CHILD_HPP_INCLUDED

namespace boost { namespace dispatch { namespace meta
{
  template<typename Expr, typename Enable = void>
  struct is_terminal : boost::mpl::false_ {};

  template<typename Expr>
  struct is_terminal< Expr
                    , typename boost::
                      enable_if< boost::proto::is_expr<Expr> >::type
                    >
  : boost::is_same  < typename boost::proto::tag_of<Expr>::type
                    , boost::proto::tag::terminal
                    >::type
  {};
} } }

namespace boost { namespace dispatch { namespace details
{
  namespace result_of
  {
    template<typename Expr, typename Enable = void>
    struct as_child : boost::dispatch::meta::strip<Expr> { };

    template<typename Expr>
    struct as_child < Expr
                    , typename boost::enable_if< meta::is_terminal<Expr> >::type
                    >
    {
      typedef Expr& type;
    };
  }
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<typename Expr>
  typename boost::disable_if< is_terminal<Expr>
                            , Expr
                            >::type
  as_child(Expr const& expr)
  {
    return expr;
  }

  template<typename Expr>
  typename boost::enable_if < is_terminal<Expr>
                            , boost::reference_wrapper<Expr>
                            >::type
  as_child(Expr& expr)
  {
    return boost::ref(expr);
  }

  template<typename Expr>
  typename boost::enable_if < is_terminal<Expr>
                            , boost::reference_wrapper<Expr const>
                            >::type
  as_child(Expr const& expr)
  {
    return boost::cref(expr);
  }
} } }

#endif
