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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_GAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_gamma gamma
 *
 * \par Description
 * Gamma function
 * \par Formula
 * \f[ \Gamma(a_0)=\int_0^\infty t^{a_0-1}e^{-t}dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/gamma.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::gamma_(A0)>::type
 *     gamma(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of gamma
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
     * \brief Define the tag gamma_ of functor gamma
     *        in namespace nt2::tag for toolbox euler
    **/
    struct gamma_ : ext::elementwise_<gamma_> { typedef ext::elementwise_<gamma_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::gamma_, gamma, 1)
}

#endif

// modified by jt the 25/12/2010
