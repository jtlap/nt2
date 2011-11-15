//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LENGTH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::length function
 */

#include <boost/fusion/include/fold.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2
{
  //============================================================================
  /*!
   * Compute largest dimension of an entity.
   *
   * \param xpr Expression to compute the length in number of elements
   * \return The largest dimension of the size of \c xpr
   */
  //============================================================================
  template<class T> inline std::size_t length( T const& xpr )
  {
    typedef typename 
          meta::strip<typename meta::call<tag::extent_(T)>::type>::type type;

     return boost::fusion::fold ( nt2::extent(xpr)
                                , typename type::value_type(1)
                                , functor<tag::max_>() 
                                );
  }
}
#endif
