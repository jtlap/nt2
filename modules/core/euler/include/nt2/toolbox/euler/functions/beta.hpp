//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_BETA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_BETA_HPP_INCLUDED

#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_beta beta
 *
 * \par Description
 * Beta function
 * \par Formula
 * \f[ B(a_0,a_1)=\int_0^1 t^{a_0-1}(1-t)^{a_1-1}dt = \frac{\Gamma(a_0)\Gamma(a_1)}{\Gamma(a_0+a_1)}\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/beta.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::beta_(A0,A0)>::type
 *     beta(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of beta
 * \param a1 the second parameter of beta
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag beta_ of functor beta
     *        in namespace nt2::tag for toolbox euler
    **/
    struct beta_ : ext::elementwise_<beta_> { typedef ext::elementwise_<beta_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::beta_, beta, 2)
}

#endif

// modified by jt the 25/12/2010
