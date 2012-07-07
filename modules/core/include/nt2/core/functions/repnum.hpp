//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_REPNUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_REPNUM_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    struct  repnum_
          : ext::generative_<repnum_> { typedef ext::generative_<repnum_> parent; };
  }

  #define M0(z,n,t)                                         \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::repnum_, repnum, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register repnum_ as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::repnum_,Domain,N,Expr>   : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::repnum_,Domain,N,Expr>     : generative_size_of<Expr>
  {};
} } }

#endif
