/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_CIF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CIF_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/cif.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/details/generative.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    struct cif_ : ext::generative_<cif_>
    {
      typedef ext::generative_<cif_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, cif, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, cif, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, cif, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, matlab_cols, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, matlab_cols, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cif_, matlab_cols, 3)
}

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Register cif as a generative expression
  //============================================================================
  template<class Domain, class Expr, int N>
  struct generator<tag::cif_,Domain,N,Expr>   : generative_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct size_of<tag::cif_,Domain,N,Expr>     : generative_size_of<Expr>
  {};
} } }

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of cif.hpp
// /////////////////////////////////////////////////////////////////////////////
