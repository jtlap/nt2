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
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLINT_2_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLINT_2_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup elliptic
 * \defgroup elliptic_ellint_2 ellint_2
 *
 * \par Description
 * Complete elliptic integral of the second kind
 * \par Formula
 * \f[E(a_0) = \int_0^{\pi/2} (1-a_0^2\sin^2 t)^{\frac12} dt\f]
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/ellint_2.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::ellint_2_(A0)>::type
 *     ellint_2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ellint_2
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
     * \brief Define the tag ellint_2_ of functor ellint_2 
     *        in namespace nt2::tag for toolbox elliptic
    **/
    struct ellint_2_ : ext::elementwise_<ellint_2_> {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::ellint_2_, ellint_2, 1)
}

#endif

// modified by jt the 25/12/2010
