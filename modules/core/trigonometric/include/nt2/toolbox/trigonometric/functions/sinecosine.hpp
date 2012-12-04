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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_sinecosine sinecosine
 *
 * \par Description
 * templatized simultaneous sine and cosine.
 * \arg tie(si,co) = sinecosine<T>(a) returns the sine and cosine of a.
 * \arg si = sinecosine<T>(a,co) returns the sine of a and put the cosine of a in co.
 * \arg sinecosine<T>(a,si,co) returns 0 and and put the sine of a in si and the cosine cosine of a in co.
 * \par please consult cosine or sine documentation for the use of the T mode template parameter
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sinecosine.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class T,class A0> inline
 *   typename boost::dispatch::meta::call<tag::sinecosine(A0 const&,A0 const&)
 *                                       >::type
 *   sinecosine(A0 const& a);
 *
 *   template<class T,class A0> inline
 *   A0 sinecosine(A0 const& a,A0,A0& si);
 *
 *   template<class T,class A0> inline
 *   int sinecosine(A0 const& a,A0,A0& si,A0& co);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sinecosine
 *
 * \param T template parameter of sinecosine, used to control accuracy and speed
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
     * \brief Define the tag sinecosine_ of functor sinecosine
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    template < class T > struct sinecosine_ : ext::elementwise_< sinecosine_<T> > { typedef ext::elementwise_< sinecosine_<T> > parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&), 2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&)(A2&),3)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&)(A2&)(A2&),3)

}

#endif

// modified by jt the 25/12/2010
