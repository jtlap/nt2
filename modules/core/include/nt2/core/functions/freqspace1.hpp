//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE1_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE1_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
/*!
 * \ingroup core
 * \defgroup core_freqspace1 freqspace1
 *
 * \par Description
 * Frequency spacing for frequency response. 1D case
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/freqspace1.hpp>
 * \endcode
 *
 *   f =  freqspace1(n, whole_, as<T>())
 *   f =  freqspace1(n, as<T>())
 *
 *   f = freqspace1(n, as<T>()) returns the 1-d frequency vector f assuming n
 *                              equally spaced points around the unit circle.
 *                              f = _(0, 2/n, 1).
 *   f = freqspace1(n, whole_, as<T>()) returns all n equally spaced points.
 *                                 In this case, f = _(0, 2/n, 2*(n-1)/n).
 *
 * T can be any floating type
**/

/* 'whole'
  [f]       = freqspace(n)
  [f]       = freqspace(n, whole_, as<T>())
  [f]       = freqspace(n,         as<T>())
  [f1, f2]  = freqspace(n)
  [f1, f2]  = freqspace([m, n])
  [f1, f2]  = freqspace([m, n], meshgrid_)
  [f1, f2]  = freqspace([m, n], as<T>())
  [f1, f2]  = freqspace([m, n], meshgrid_,  as<T>())
 */
namespace nt2
{
  namespace tag
  {
    struct freqspace1_ : ext::generative_<freqspace1_>
    {
      typedef ext::generative_<freqspace1_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace1_, freqspace1, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace1_, freqspace1, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace1_, freqspace1, 1)
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register colon as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::freqspace1_,Domain,N,Expr> : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::freqspace1_,Domain,N,Expr>   : generative_size_of<Expr>
  {};
} } }

#endif
