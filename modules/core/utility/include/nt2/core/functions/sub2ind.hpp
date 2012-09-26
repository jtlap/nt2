//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
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
  namespace tag
  {
    struct sub2ind_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * Determines the C linear index equivalents to the specified subscripts for
   * each dimension of an N-dimensional container of size .
   *
   * \param size Size sequence of target container
   * \param pos  Subscript to convert
   * \param base Optional base index sequence for non canonic container
   * \return A C linear index pointing to the same element than \c pos.
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sub2ind_, sub2ind, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sub2ind_, sub2ind, 3)
}

#endif
