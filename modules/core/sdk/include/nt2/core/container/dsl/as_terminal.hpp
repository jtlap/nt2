//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_AS_TERMINAL_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_AS_TERMINAL_HPP_INCLUDED

#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace nt2 { namespace container
{
  template<class Semantic, class Expr = int, class Enable = void>
  struct as_terminal
       : boost::dispatch::meta::terminal_of<Semantic>
  {
    static typename as_terminal::type init(Expr)
    {
      return typename as_terminal::type();
    }
  };

  // TODO: check interleaving and storage order is same
  template<class Semantic, class Expr>
  struct as_terminal< Semantic
                    , Expr
                    , typename boost::
                      enable_if_c< boost::remove_reference<Expr>::type::proto_arity_c == 0
                                && boost::is_same< typename boost::remove_reference<Expr>::type::value_type
                                                 , typename Semantic::value_type >::value
                                                 >::type
                    >
  {
    typedef Expr type;
    static type init(Expr expr)
    {
      return expr;
    }
  };
} }

#endif
