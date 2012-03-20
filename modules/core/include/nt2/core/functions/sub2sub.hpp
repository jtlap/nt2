//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SUB2SUB_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SUB2SUB_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::sub2sub function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag { struct sub2sub_ : ext::unspecified_<sub2sub_> { typedef ext::unspecified_<sub2sub_> parent; }; }

  //============================================================================
  /*!
   * Determines a N-dimensional subscript from a M-dimensional subscript.
   *
   * \param sizein  Input size M
   * \param pos     Subscript to convert
   * \param sizeout Output size N
   * \return The subscript of size N corresponding to pos of size M.
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sub2sub_, sub2sub, 3)
}

#endif
