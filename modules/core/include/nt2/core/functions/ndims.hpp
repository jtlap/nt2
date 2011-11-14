//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
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

#include <algorithm>
#include <nt2/core/functions/extent.hpp>

namespace nt2
{
  //============================================================================
  /*!
   * Compute the number of dimensions of a given entity.
   *
   * \param xpr Expression to compute the size in number of dimensions
   * \return The number of elements dimensions required to store \c xpr
   */
  //============================================================================
  template<class T> inline std::size_t ndims( T const& xpr )
  {
    typename meta::call<tag::extent_(T const&)>::type sz  = nt2::extent(xpr);
    std::size_t i = sz.size();

    while((i != 0) && (sz[i-1] == 1)) { i--; }
    return std::max ( std::size_t(2)
                    , (i == 0 ? sz.size() : std::max(std::size_t(2),i)) 
                    );
  }
}
#endif
