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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_POW_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_POW_ABS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_pow_abs pow_abs
 *
 * \par Description
 * Pow_Abser function: ${a_0}^{a_1}$
 * \par
 * $0^0$ returns 1
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/pow_abs.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::pow_abs_(A0,A0)>::type
 *     pow_abs(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of pow_abs
 * \param a1 the second parameter of pow_abs
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
     * \brief Define the tag pow_abs_ of functor pow_abs
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct pow_abs_ : ext::elementwise_<pow_abs_> { typedef ext::elementwise_<pow_abs_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::pow_abs_, pow_abs, 2)
}

#endif

// modified by jt the 25/12/2010
