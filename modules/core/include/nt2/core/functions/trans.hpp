//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRANS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRANS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::trans function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct trans_ : ext::elementwise_<trans_>
    {
      typedef ext::elementwise_<trans_> parent;
    };
    struct offset_trans_ : ext::elementwise_<offset_trans_>
    {
      typedef ext::elementwise_<offset_trans_>  parent;
    };
   }

  //============================================================================
  /*!
   * transpose a matrix
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trans_       , trans, 1)
}


#endif
