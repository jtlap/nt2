//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CIF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CIF_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the cif function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/cif.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/functions/details/generative_preprocessor.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for cif functor
     **/
    struct cif_ : ext::generative_<cif_>
    {
      typedef ext::generative_<cif_> parent;
    };
  }

  #define M0(z,n,t)                                   \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, cif, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<tag::cif_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  size_of<tag::cif_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

namespace nt2 { namespace ext
{
  NT2_PP_MAKE_GENERATIVE( cif, (nt2::tag::cif_,nt2::tag::cif_) )
} }

#endif
