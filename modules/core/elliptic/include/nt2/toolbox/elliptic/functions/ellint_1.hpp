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
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLINT_1_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLINT_1_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup elliptic
 * \defgroup elliptic_ellint_1 ellint_1
 *
 * \par Description
 * Complete elliptic integral of the first kind
 * \par Formula
 * \f[K(a_0) = \int_0^{\pi/2} \sqrt{1-a_0^2\sin^2 t} dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ellint_1.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::ellint_1_(A0)>::type
 *     ellint_1(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ellint_1
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
     * \brief Define the tag ellint_1_ of functor ellint_1
     *        in namespace nt2::tag for toolbox elliptic
    **/
    struct ellint_1_ : ext::elementwise_<ellint_1_> { typedef ext::elementwise_<ellint_1_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::ellint_1_, ellint_1, 1)
}

#endif

// modified by jt the 25/12/2010
