//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LENGTH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::length function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct length_ : ext::unspecified_<length_> { typedef ext::unspecified_<length_> parent; }; }

  //============================================================================
  /*!
   * Compute largest dimension of an entity.
   *
   * \param xpr Expression to compute the length in number of elements
   * \return The largest dimension of the size of \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::length_, length, 1)
}

#endif
