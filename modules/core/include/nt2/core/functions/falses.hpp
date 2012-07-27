//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FALSES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FALSES_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <nt2/core/functions/details/generative_preprocessor.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    struct  falses_
          : ext::generative_<falses_> { typedef ext::generative_<falses_> parent; };
  }

  #define M0(z,n,t)                                       \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::falses_, falses, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

//==============================================================================
// Setup infs generator traits
//==============================================================================
namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr, int N>
  struct value_type<tag::falses_,Domain,N,Expr>  : generative_value_type<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::falses_,Domain,N,Expr>     : generative_size_of<Expr>
  {};
} } }

//==============================================================================
// Setup infs specialization
//==============================================================================
namespace nt2 { namespace ext
{
  NT2_PP_MAKE_GENERATIVE( falses, (nt2::tag::falses_,nt2::tag::False) )
} }
#endif
