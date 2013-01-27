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
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_J0_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_J0_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup bessel
 * \defgroup bessel_j0 j0
 *
 * \par Description
 * Bessel function of the first kind of order 0.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/j0.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::j0_(A0)>::type
 *     j0(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of j0
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
     * \brief Define the tag j0_ of functor j0
     *        in namespace nt2::tag for toolbox bessel
    **/
    struct j0_ : ext::elementwise_<j0_> { typedef ext::elementwise_<j0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::j0_, j0, 1)
}

#endif

// modified by jt the 25/12/2010
