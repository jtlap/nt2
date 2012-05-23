//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <nt2/include/functions/freqspace1.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_freqspace2 freqspace2
 *
 * \par Description
 * Elementary Least square
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/freqspace2.hpp>
 * \endcode
 * 
 *   tie(f1,f2) = freqspace2(n, as_<T>) returns the 2-d frequency range vectors
 *                              f1 and f2 for an n-by-n matrix.
 *   tie(f1,f2) = freqspace2(m, n, as_<T>) or  freqspace2(of_size(m, n), as_<T>)
                                returns the 2-d frequency range 
 *                              vectors for an m-by-n matrix.
 *
 *  this means for n odd,  f = _(-1+1/n,2/n,1-1/n).
 *                 n even, f = _(-1    ,2/n,1-2/n).
 *
 *    tie(f1,f2) = freqspace2(...,_, as_<T>) is equivalent to
 *    tie(f1,f2) = freqspace2(..., as_<T>);  tie(f1,f2) = meshgrid(f1,f2);
 *
**/
namespace nt2
{
  namespace tag
  {
    struct freqspace2_ : ext::generative_<freqspace2_>
    {
      typedef ext::generative_<freqspace2_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace2_, freqspace2, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace2_, freqspace2, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace2_, freqspace2, 1)
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register colon as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::freqspace2_,Domain,N,Expr> : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::freqspace2_,Domain,N,Expr>   : generative_size_of<Expr>
  {};
} } }

#endif

