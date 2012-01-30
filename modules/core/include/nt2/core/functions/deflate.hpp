//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DEFLATE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DEFLATE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::deflate function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag { struct deflate_ : ext::unspecified_<deflate_> {}; }

  //============================================================================
  /*!
   * Turns a N dimensions position into a 2D position fitting in the same
   * dimension space.
   *
   * \param size Size sequence of target container
   * \param pos  Subscript to convert
   * \param base Optionnal base index sequence for non canonic container
   * \return A 2D position pointing to the same element than \c pos.
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::deflate_, deflate, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::deflate_, deflate, 3)
}

#endif
