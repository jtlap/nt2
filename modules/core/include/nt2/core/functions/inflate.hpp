//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_INFLATE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_INFLATE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::inflate function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag { struct inflate_ : ext::unspecified_<inflate_> {}; }

  //============================================================================
  /*!
   * Turns a 1D position into a 2D position fitting in the same dimension space.
   *
   * \param size Size sequence of target container
   * \param pos  Subscript to convert
   * \param base Optionnal base index sequence for non canonic container
   * \return A 2D position pointing to the same element than \c pos.
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::inflate_, inflate, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::inflate_, inflate, 3)
}

#endif
