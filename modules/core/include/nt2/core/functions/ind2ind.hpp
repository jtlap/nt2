//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_IND2IND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_IND2IND_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::ind2ind function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct ind2ind_ : ext::unspecified_<ind2ind_>
    {
      typedef ext::unspecified_<ind2ind_> parent;
    };
  }

  //============================================================================
  /*!
   * Translate a linear index between two dimensions sets
   *
   * \param sizein  Input size M
   * \param pos     Index to convert
   * \param sizeout Output size N
   * \return The index inside N corresponding to the index inside M.
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ind2ind_, ind2ind, 3)
}

#endif
