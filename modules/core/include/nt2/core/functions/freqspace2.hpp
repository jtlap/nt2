//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE2_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the freqspace2 function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/options.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the freqspace2 functor
    **/
    struct freqspace2_ : ext::generative_<freqspace2_>
    {
      typedef ext::generative_<freqspace2_> parent;
    };
  }

  /*!
    tie(f1,f2) = freqspace2(n, as_<T>) returns the 2-d frequency range vectors
                               f1 and f2 for an n-by-n matrix.
    tie(f1,f2) = freqspace2(m, n, as_<T>) or  freqspace2(of_size(m, n), as_<T>)
                                returns the 2-d frequency range
                               vectors for an m-by-n matrix.

   this means for n odd,  f = _(-1+1/n,2/n,1-1/n).
                  n even, f = _(-1    ,2/n,1-2/n).

     tie(f1,f2) = freqspace2(...,_, as_<T>) is equivalent to
     tie(f1,f2) = freqspace2(..., as_<T>);  tie(f1,f2) = meshgrid(f1,f2);

  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace2_, freqspace2, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace2_, freqspace2, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace2_, freqspace2, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::freqspace2_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::freqspace2_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
