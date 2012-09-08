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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_CEPHES_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_CEPHES_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_rem_pio2_cephes rem_pio2_cephes
 *
 * \par Description
 * compute the remainder modulo \f$\pi/2\f$ with cephes algorthm.
 * \par
 * This is a quick version accurate if the input
 * is in \f$[-20\pi,20\pi\f$.
 * \par
 * The reduction of the argument modulo \f$pi/2\f$ is generally
 * the most difficult part of trigonometric evaluations.
 * The accurate algorithm is over costly and implies the knowledge
 * of a few hundred \f$pi\f$ decimals
 * some simpler algorithms as this one
 * can be used, but the precision is only insured on small_ intervals.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rem_pio2_cephes.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::rem_pio2_cephes_(A0)>::type
 *     rem_pio2_cephes(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of rem_pio2_cephes
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
     * \brief Define the tag rem_pio2_cephes_ of functor rem_pio2_cephes
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct rem_pio2_cephes_ : ext::elementwise_<rem_pio2_cephes_> { typedef ext::elementwise_<rem_pio2_cephes_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_cephes_, rem_pio2_cephes,(A0 const&)(A0&)(A0&),1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_cephes_, rem_pio2_cephes,(A0 const&),1)
}

#endif

// modified by jt the 25/12/2010
