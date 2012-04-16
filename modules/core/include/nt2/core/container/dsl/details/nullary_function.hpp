//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_NULLARY_FUNCTION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_NULLARY_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace container { namespace ext
{
  //==========================================================================
  // Generator nullary function call case - handle expr()
  //==========================================================================
  template<class Domain, class Expr>
  struct generator<tag::function_, Domain, 1, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::type child0;

    typedef child0 result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e);
    }
  };
} } }

#endif

