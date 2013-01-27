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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_PROPER_TANPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_PROPER_TANPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_proper_tanpi proper_tanpi
 *
 * \par Description
 * tangent of angle in \f$\pi\f$ multiples: \f$\tan(\pi a_0)\f$.
 * a0 between -0.5 and +0.5
 * This function is the inverse of atanpi and so is such that proper_tanpi(0.5) is inf
 * and  proper_tanpi(-0.5) is -inf
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/proper_tanpi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::proper_tanpi_(A0)>::type
 *     proper_tanpi(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of proper_tanpi
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
     * \brief Define the tag proper_tanpi_ of functor proper_tanpi
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct proper_tanpi_ : ext::elementwise_<proper_tanpi_> { typedef ext::elementwise_<proper_tanpi_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::proper_tanpi_, proper_tanpi, 1)
}

#endif

// modified by jt the 25/12/2010
