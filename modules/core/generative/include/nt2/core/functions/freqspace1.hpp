//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE1_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE1_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the  function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the functor
    **/
    struct freqspace1_ : ext::generative_<freqspace1_>
    {
      typedef ext::generative_<freqspace1_> parent;
    };
  }

  /*!
    f =  freqspace1(n, whole_, as<T>())
    f =  freqspace1(n, as<T>())

    f = freqspace1(n, as<T>()) returns the 1-d frequency vector f assuming n
                               equally spaced points around the unit circle.
                               f = _(0, 2/n, 1).
    f = freqspace1(n, whole_, as<T>()) returns all n equally spaced points.
                                       In this case, f = _(0, 2/n, 2*(n-1)/n).
    T can be any floating type
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace1_, freqspace1, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace1_, freqspace1, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace1_, freqspace1, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::freqspace1_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::freqspace1_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
