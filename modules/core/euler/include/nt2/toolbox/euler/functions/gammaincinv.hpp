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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_GAMMAINCINV_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_GAMMAINCINV_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_gammaincinv gammaincinv
 *
 * \par Description
 * Inverse of Incomplete Gamma function
 * \par Formula
 * \f[ if y = gammaincinv(a, x)=\int_0^\a t^{x-1}e^{-t}dt\f]
 * x = gammaincinv(a, y)
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/gammaincinv.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::gammaincinv_(A0, A1)>::type
 *     gammaincinv(const A0 & x, const A0& a);
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
     * \brief Define the tag gammaincinv_ of functor gammaincinv 
     *        in namespace nt2::tag for toolbox euler
    **/
    struct gammaincinv_ : ext::elementwise_<gammaincinv_> { typedef ext::elementwise_<gammaincinv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::gammaincinv_, gammaincinv, 2)
}

#endif

// modified by jt the 25/12/2010
