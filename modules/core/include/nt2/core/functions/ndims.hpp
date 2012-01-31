//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NDIMS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NDIMS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::nbdims function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag { struct ndims_ : ext::unspecified_<ndims_> { typedef ext::unspecified_<ndims_> parent; }; }

  //============================================================================
  /*!
   * Compute the number of dimensions of a given entity.
   *
   * \param xpr Expression to compute the size in number of dimensions
   * \return The number of elements dimensions required to store \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ndims_, ndims, 1)
}

#endif
