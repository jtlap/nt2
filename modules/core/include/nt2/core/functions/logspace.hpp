//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LOGSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LOGSPACE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
/*!
 * \ingroup core
 * \defgroup core_logspace logspace
 *
 * \par Description
 * logspace logarithmically spaced vector.
 *    logspace(x1, x2) generates a row vector of 50 logarithmically
 *    equally spaced points between decades 10^x1 and 10^x2.  if x2
 *    is pi, then the points are between 10^x1 and pi. and return double values
 *
 *    logspace(x1, x2, as<T>()) return type T values
 *    logspace(x1, x2, n) and logspace(x1, x2, n, as<T>()) return n values instead of 50
 *    logspace(x1, x2, n, nt2::regular_) and logspace(x1, x2, n, as<T>(), nt2::regular_)
 *       make no special treatment for x2 ==  pi
 *
 *    for n = 1, logspace returns 10^x2... which the same pi treatments
 *
 *    T can be any floating type
 *
 * \par header file
 * 
 * \code
 * #include <nt2/include/functions/logspace.hpp>
 * \endcode
**/

namespace nt2
{
  struct regular_t {};
  const meta::as_<regular_t> regular_ = {};
  namespace tag
  {
    struct logspace_ : ext::generative_<logspace_>
    {
      typedef ext::generative_<logspace_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::logspace_, logspace, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::logspace_, logspace, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::logspace_, logspace, 4)
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register colon as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::logspace_,Domain,N,Expr> : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::logspace_,Domain,N,Expr>   : generative_size_of<Expr>
  {};
} } }

#endif

