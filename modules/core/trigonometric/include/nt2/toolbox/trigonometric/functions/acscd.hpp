//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_ACSCD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_ACSCD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_acscd acscd
 *
 * \par Description
 * inverse cosecant in degree.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/acscd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::acscd_(A0)>::type
 *     acscd(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of acscd
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
     * \brief Define the tag acscd_ of functor acscd
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct acscd_ : ext::elementwise_<acscd_> { typedef ext::elementwise_<acscd_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::acscd_, acscd, 1)
}

#endif

// modified by jt the 25/12/2010
