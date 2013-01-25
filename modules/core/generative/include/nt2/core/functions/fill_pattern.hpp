//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FILL_PATTERN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FILL_PATTERN_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the fill_pattern function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for fill_pattern functor
    **/
    struct fill_pattern_ : ext::elementwise_<fill_pattern_>
    {
      typedef ext::elementwise_<fill_pattern_> parent;
    };
  }

  #define M0(z,n,t)                                                     \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::fill_pattern_, fill_pattern, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::fill_pattern_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::fill_pattern_,Domain,N,Expr>
        : meta::boxed_size<Expr,0>
  {};
} }

#endif
