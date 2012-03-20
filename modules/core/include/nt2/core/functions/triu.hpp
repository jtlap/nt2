//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIU_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIU_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::triu function
 */

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag
  {
    /*!
     * \brief Define the tag triu_ of functor triu
     *        in namespace nt2::tag for toolbox core
     **/
    
    struct triu_ : ext::unspecified_<triu_> { typedef ext::unspecified_<triu_> parent; };
  }

  //============================================================================
  /*!
   * superior triangular part of a 2D table.
   *
   * \param xpr 2D table (must verify is_matrix(a))
   * triu(a)(i, j)      is equal to: (i <= j)    ? a(i, j) : 0
   * triu(a, k)(i, j)   is equal to: (i <= j+k)  ? a(i, j) : 0
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::triu_, triu, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::triu_, triu, 2)
}

#endif
