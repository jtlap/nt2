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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ACOTH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ACOTH_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_acoth acoth
 *
 * \par Description
 * hyperbolic cotangent argument \f$\frac12\frac{a_0^2+1}{a_0^2-1}\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/acoth.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::acoth_(A0)>::type
 *     acoth(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of acoth
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
     * \brief Define the tag acoth_ of functor acoth
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct acoth_ : ext::elementwise_<acoth_> { typedef ext::elementwise_<acoth_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::acoth_, acoth, 1)
}

#endif

// modified by jt the 25/12/2010
