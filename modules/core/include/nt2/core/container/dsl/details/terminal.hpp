//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_TERMINAL_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_TERMINAL_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>

namespace nt2 { namespace container { namespace ext
{
  //==========================================================================
  // Generator case for terminals
  //==========================================================================
  template<class Tag, class Domain, class Expr>
  struct generator<Tag, Domain, 0, Expr>
  {
    typedef expression< typename boost::remove_const<Expr>::type
                      , typename boost::proto::result_of::value<Expr&>::type
                      > result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif

