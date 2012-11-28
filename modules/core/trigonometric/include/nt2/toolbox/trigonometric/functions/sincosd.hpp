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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINCOSD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINCOSD_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_sincosd sincosd
 *
 * \par Description
 * simultaneous sine and cosine from angle in degree
 * \arg tie(si,co) = sincosd(a) returns the sine and cosine of a.
 * \arg si = sincosd(a,co) returns the sine of a and put the cosine of a in co.
 * \arg sincosd(a,si,co) returns 0 and and put the sine of a in si and the cosine cosine of a in co.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sincosd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::sincosd(A0 const&,A0 const&)
 *                                       >::type
 *   sincosd(A0 const& a);
 *
 *   template<class A0> inline
 *   A0 sincosd(A0 const& a,A0,A0& si);
 *
 *   template<class A0> inline
 *   int sincosd(A0 const& a,A0,A0& si,A0& co);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sincosd
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
     * \brief Define the tag sincosd_ of functor sincosd
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct sincosd_ : ext::elementwise_<sincosd_> { typedef ext::elementwise_<sincosd_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::sincosd_, sincosd, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincosd_, sincosd,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincosd_, sincosd,(A0 const&)(A1&)(A2&),3)
}

#endif

// modified by jt the 25/12/2010
