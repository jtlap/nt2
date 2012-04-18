//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIRSTNONSINGLETON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIRSTNONSINGLETON_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::firstnonsingleton function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct firstnonsingleton_ : boost::dispatch::tag::formal_ { typedef boost::dispatch::tag::formal_ parent; }; }

  //============================================================================
  /*!
   * Find the first non singleton value 
   *
   * \param xpr Expression to find the first non singleton value
   * \return The value of the fisrt non singleton value
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::firstnonsingleton_, firstnonsingleton, 1)
}

#endif
