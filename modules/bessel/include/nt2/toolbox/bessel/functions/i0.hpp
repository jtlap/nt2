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
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_I0_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_I0_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup bessel
 * \defgroup bessel_i0 i0
 *
 * \par Description
 * Modified Bessel function of the first kind of order 0.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/i0.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::i0_(A0)>::type
 *     i0(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of i0
 * 
 * \return an integer value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag i0_ of functor i0 
     *        in namespace nt2::tag for toolbox bessel
    **/
    struct i0_ : ext::elementwise_<i0_> { typedef ext::elementwise_<i0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::i0_, i0, 1)
}

#endif

// modified by jt the 25/12/2010
