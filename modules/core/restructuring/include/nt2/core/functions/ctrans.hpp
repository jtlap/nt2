//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CTRANS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CTRANS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::ctrans function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct ctrans_ : ext::elementwise_<ctrans_>
    {
      typedef ext::elementwise_<ctrans_> parent;
    };
  }

  //============================================================================
  /*!
   * conjugate and transpose a matrix. On real matrice this is just transpose
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ctrans_, ctrans, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ctrans_, ctranspose, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ctrans_, ct    , 1)
}



#endif
