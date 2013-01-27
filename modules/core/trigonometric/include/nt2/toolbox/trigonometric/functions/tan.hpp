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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_TAN_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_TAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_tan tan
 *
 * \par Description
 * tangent.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tan.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::tan_(A0)>::type
 *     tan(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of tan
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
     * \brief Define the tag tan_ of functor tan
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct tan_ : ext::elementwise_<tan_> { typedef ext::elementwise_<tan_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::tan_, tan, 1)
}

#endif

// modified by jt the 25/12/2010
