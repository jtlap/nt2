/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_SEMANTIC_OF_HPP_INCLUDED
#define NT2_SDK_DSL_SEMANTIC_OF_HPP_INCLUDED

#include <nt2/sdk/meta/enable_if_type.hpp>

////////////////////////////////////////////////////////////////////////////////
// For a given proto expression class, retrieves its semantic info as a type
// Expression semantic info is void by design while SemanticRichExpression
// types expose a semantic_type that can be retrieved here.
// Such information are used into expression hierarchy.
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Expression, class Enable = void>
  struct semantic_of
  {
    typedef void type;
  };

  template< class Expression >
  struct semantic_of< Expression
                    , typename
                      enable_if_type<typename Expression::semantic_type>::type
                    >
  {
    typedef typename Expression::semantic_type type;
  };
} }

#endif
