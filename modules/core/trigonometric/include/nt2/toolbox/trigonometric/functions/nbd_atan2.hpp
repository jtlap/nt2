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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_NBD_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_NBD_ATAN2_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_nbd_atan2 nbd_atan2
 *
 * \par Description
 * nbd_atan2 function.
 * The two-argument function nbd_atan2 is a variation of the arctangent function.
 * BE WARNED
 * nbd stands for "no bounds": atan2 is suposed to be faster than atan2 at the price that
 * values for -inf, inf and nan are erroneous !
 *
 * \par
 * For any real arguments a0 and a1 not both equal to zero, nbd_atan2(a0, a1)
 * is the angle in radians between the positive x-axis of a plane and the point
 * given by the coordinates (a1, a0) on it.
 * \par
 * It is the angle in \f$[-\pi,\pi[ \f$ such that
 * \f$a1/\sqrt{a_0^2+a_1^2}\f$ and \f$a0/\sqrt{a_0^2+a_1^2}\f$are respectively the sine and the cosine.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/nbd_atan2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::nbd_atan2_(A0,A0)>::type
 *     nbd_atan2(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of nbd_atan2
 * \param a1 the second parameter of nbd_atan2
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag nbd_atan2_ of functor nbd_atan2
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct nbd_atan2_ : ext::elementwise_<nbd_atan2_> { typedef ext::elementwise_<nbd_atan2_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::nbd_atan2_, nbd_atan2, 2)
}

#endif

// modified by jt the 25/12/2010
