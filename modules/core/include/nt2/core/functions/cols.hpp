/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_COLS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/cols.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    struct cols_ : ext::generative_<cols_>
    {
      typedef ext::generative_<cols_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cols_, cols, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cols_, cols, 3)
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register cols as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::cols_,Domain,N,Expr>   : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::cols_,Domain,N,Expr>     : generative_size_of<Expr>
  {};
} } }

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of cols.hpp
// /////////////////////////////////////////////////////////////////////////////
