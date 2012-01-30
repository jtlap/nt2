//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_J1_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_J1_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup bessel
 * \defgroup bessel_j1 j1
 *
 * \par Description
 * Bessel function of the first kind of order 1.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/j1.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::j1_(A0)>::type
 *     j1(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of j1
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag j1_ of functor j1 
     *        in namespace nt2::tag for toolbox bessel
    **/
    struct j1_ : ext::elementwise_<j1_> {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::j1_, j1, 1)
}

#endif

// modified by jt the 25/12/2010
