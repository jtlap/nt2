//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_VALUE_TYPE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_VALUE_TYPE_HPP_INCLUDED

#include <boost/proto/transform.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Extension of value_type to handle function call nodes
  // The returned value is the value_type of the leftmost children of the node
  //============================================================================
  template<class Expr, class Domain, int N>
  struct value_type<tag::function_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::type   child0;

    typedef typename boost::dispatch::meta::
            scalar_of < typename boost::dispatch::meta::
                        semantic_of<child0>::type
                      >::type                                           type;
  };
} } }

#endif
