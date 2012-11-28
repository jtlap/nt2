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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COTANGENT_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COTANGENT_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_cotangent cotangent
 *
 * \par Description
 * templated cosine.
 * \par
 * see cosine for details
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cotangent.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::cotangent_(A0)>::type
 *     cotangent(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cotangent
 *
 * \param T template parameter of cotangent, used to control accuracy and speed
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
     * \brief Define the tag cotangent_ of functor cotangent
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    template <class T> struct cotangent_ : ext::elementwise_< cotangent_<T> > { typedef ext::elementwise_< cotangent_<T> > parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cotangent_<A0> , cotangent, (A1 const&), 2)
}

#endif

// modified by jt the 25/12/2010
