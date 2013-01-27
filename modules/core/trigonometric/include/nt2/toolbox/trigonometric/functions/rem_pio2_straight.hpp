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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_STRAIGHT_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_STRAIGHT_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_rem_pio2_straight rem_pio2_straight
 *
 * \par Description
 * compute the remainder modulo \f$\pi/2\f$ with straight algorthm in \f$[\pi/4,\pi/2\f$.
 * \par
 * This is a very quick version accurate if the input
 * is in \f$[\pi/4,\pi/2\f$. In fact it only subsstract \f$\pi/2\f$ to the input
 * so it can be viewed as a specially accurate minuspio_2 function outside
 * the interval in which it can be used as a substitute to rem_pio2.
 * \par
 * The reduction of the argument modulo \f$pi/2\f$ is generally
 * the most difficult part of trigonometric evaluations.
 * The accurate algorithm is over costly and implies the knowledge
 * of a few hundred \f$pi\f$ decimals
 * some simpler algorithms as this one
 * can be used, but the precision is only insured on specific intervals.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rem_pio2_straight.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::rem_pio2_straight_(A0)>::type
 *     rem_pio2_straight(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of rem_pio2_straight
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
     * \brief Define the tag rem_pio2_straight_ of functor rem_pio2_straight
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct rem_pio2_straight_ : ext::elementwise_<rem_pio2_straight_> { typedef ext::elementwise_<rem_pio2_straight_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, rem_pio2_straight,(A0 const&)(A0&)(A0&),1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, rem_pio2_straight,(A0 const&),1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, minuspio_2,(A0 const&)(A0&)(A0&),1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, minuspio_2,(A0 const&),1)
}

#endif

// modified by jt the 25/12/2010
