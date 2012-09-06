//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DEPTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DEPTH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::depth function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct depth_ : ext::unspecified_<depth_> { typedef ext::unspecified_<depth_> parent; }; }

  //============================================================================
  /*!
   * Compute the number of element stored in a given entity.
   *
   * \param xpr Expression to compute the size in number of elements
   * \return The number of elements stored in \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::depth_, depth, 1)
}

#endif
