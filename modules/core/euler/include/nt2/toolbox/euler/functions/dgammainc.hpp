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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_DGAMMAINC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_DGAMMAINC_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_dgammainc dgammainc
 *
 * \par Description
 * Dérivative of incomplete Gamma function relative to the second parameter
 * \par Formula
 * \f[ dgammainc(x)=\int_0^\a t^{x-1}e^{-t}dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/dgammainc.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::dgammainc_(A0, A1)>::type
 *     dgammainc(const A0 & x, const A0& a);
 * }
 * \endcode
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag dgammainc_ of functor dgammainc
     *        in namespace nt2::tag for toolbox euler
    **/
    struct dgammainc_ : ext::elementwise_<dgammainc_> { typedef ext::elementwise_<dgammainc_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::dgammainc_, dgammainc, 2)
}

#endif

// modified by jt the 25/12/2010
