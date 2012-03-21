//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_EXPRESSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_EXPRESSION_HPP_INCLUDED

#include <boost/dispatch/dsl/semantic_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Semantic of NT2 expression lies in its ResultType template parameter
  //============================================================================
  template<class Expr, class ResultType>
  struct semantic_of< nt2::container::expression<Expr, ResultType> >
  {
    typedef ResultType type;
  };
} } }

#endif
