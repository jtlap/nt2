//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBAL_REDUCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBAL_REDUCTION_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::global_reduction function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct global_reduction_ : ext::unspecified_<global_reduction_> { typedef ext::unspecified_<global_reduction_> parent; }; }

  //============================================================================
  /*!
   * Compute global reduction of an expresion
   *
   * \param xpr Expression to compute the global reduction
   * \return a scalar corresponding of the global reduction of \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::global_redcution_, global_reduction, 1)
}

#endif
