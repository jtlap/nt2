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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SINHC_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SINHC_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_sinhc sinhc
 *
 * \par Description
 * hyperbolic cardinal sine: \f$\frac{\sinh(a_0)}{a_0}\f$.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sinhc.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::sinhc_(A0)>::type
 *     sinhc(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sinhc
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
     * \brief Define the tag sinhc_ of functor sinhc
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct sinhc_ : ext::elementwise_<sinhc_> { typedef ext::elementwise_<sinhc_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::sinhc_, sinhc, 1)
}

#endif

// modified by jt the 25/12/2010
