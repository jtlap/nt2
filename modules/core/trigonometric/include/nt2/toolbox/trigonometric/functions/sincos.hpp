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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINCOS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINCOS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_sincos sincos
 *
 * \par Description
 * simultaneous sine and cosine.
 * \arg tie(si,co) = sincos(a) returns the sine and cosine of a.
 * \arg si = sincos(a,co) returns the sine of a and put the cosine of a in co.
 * \arg sincos(a,si,co) returns 0 and and put the sine of a in si and the cosine cosine of a in co.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sincos.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::sincos(A0 const&,A0 const&)
 *                                       >::type
 *   sincos(A0 const& a);
 *
 *   template<class A0> inline
 *   A0 sincos(A0 const& a,A0,A0& si);
 *
 *   template<class A0> inline
 *   int sincos(A0 const& a,A0,A0& si,A0& co);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sincos
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
     * \brief Define the tag sincos_ of functor sincos
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct sincos_ : ext::elementwise_<sincos_> { typedef ext::elementwise_<sincos_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::sincos_, sincos, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincos_, sincos,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincos_, sincos,(A0 const&)(A1&)(A2&),3)

}

#endif

// modified by jt the 25/12/2010
