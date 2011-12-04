//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SUB2IND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SUB2IND_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::sub2ind function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct sub2ind_ {}; }

  //============================================================================
  /*!
   * Determines the linear index equivalents to the specified subscripts for
   * each dimension of an N-dimensional container of size . 
   *
   * \param size Size sequence of target container
   * \param pos  Subscript to convert
   * \param base Optionnal base index sequence for non canonic container
   * \return A linear index pointing to the same element than \c pos.
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sub2ind_, sub2ind, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sub2ind_, sub2ind, 3)
}

#endif
