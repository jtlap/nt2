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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_TAN_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_TAN_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_fast_tan fast_tan
 *
 * \par Description
 * tangent in the interval \f$[-\pi/4, \pi/4]\f$, nan outside.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fast_tan.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fast_tan_(A0)>::type
 *     fast_tan(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_tan
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
     * \brief Define the tag fast_tan_ of functor fast_tan 
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct fast_tan_ : ext::elementwise_<fast_tan_> { typedef ext::elementwise_<fast_tan_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_tan_, fast_tan, 1)
}

#endif

// modified by jt the 25/12/2010
