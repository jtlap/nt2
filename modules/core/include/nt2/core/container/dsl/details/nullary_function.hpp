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

#include <boost/proto/traits.hpp>
#include <nt2/core/functions/function.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2 { namespace container { namespace ext
{
  //==========================================================================
  // Generator nullary function call case - handle expr()
  //==========================================================================
  template<class Domain, class Expr>
  struct  generator<tag::function_, Domain, 1, Expr>
        : generate_as<Expr,0>
  {};
} } }

#endif

