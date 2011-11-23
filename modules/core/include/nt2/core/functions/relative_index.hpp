//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RELATIVE_INDEX_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::relative_index function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct relative_index_ {}; }

  //============================================================================
  /*!
   * Performs an index translation to be used in indexed access computation
   *
   * \param xpr Indexing expression
   * \param pos Original position   
   * \param idx Static index being computed
   * \return The number of elements dimensions required to store \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::relative_index_, relative_index, 3)
}

#endif
