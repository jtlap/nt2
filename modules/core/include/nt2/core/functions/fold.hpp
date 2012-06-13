//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FOLD_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::fold function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag { struct fold_ : ext::unspecified_<fold_> { typedef ext::unspecified_<fold_> parent; }; }
  //============================================================================
  /*!
   * Folds elements of \c a1, possibly in parallel, and returns the result.
   *
   * \param a0 Expression to reduce
   * \param a1 Functor to initialize the accumulator with
   * \param a2 Function to apply for binary reduction, first argument is accumulator
   * \param a3 Function to apply for unary reduction (for SIMD usage)
   * \return nothing
   */
  //============================================================================
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::fold_, fold, (A0 const&)(A1 const&)(A2 const&)(A3 const&), 4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::fold_, fold, (A0&)(A1 const&)(A2 const&)(A3 const&), 4)

}

#endif
