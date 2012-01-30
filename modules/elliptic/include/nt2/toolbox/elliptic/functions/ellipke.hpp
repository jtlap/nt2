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
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLIPKE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLIPKE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup elliptic
 * \defgroup elliptic_ellipke ellipke
 *
 * \par Description
 * Complete elliptic integrals of first and second kind
 * \arg k = ellipke(m) returns the complete elliptic integral of the first kind of m.
 * \arg tie(k,e) = ellipke(m) returns the complete elliptic integral of the first and second kinds.
 * \arg tie(k,e) = ellipke(m,tol) computes the complete elliptic integral to accuracy tol.
 *  The default is Eps<A0>()
 * tol allows a compromise between less accurate but more quickly computed answer.
 * \par
 * the function also be called as indicated in the synopsis: ellipke(m,tol,k,e)
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/ellipke.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::ellipke_(A0 const&,A0 const&)
 *                                       >::type
 *   ellipke(A0 const& m,A0 const& tol=Eps<A0>());
 *    
 *   template<class A0> inline
 *   int ellipke(A0 const& m,A0 const& tol,A0& k,A0&e);
 * }
 * \endcode
 *
 * \param a0 the first parameter of ellipke, outside of $[0,1]$ the result is nan
 * \param a1 the second parameter of ellipke, optional tolerance
 * \param a2 the third parameter of ellipke, if present, first kind result
 * \param a3 the fourth parameter of ellipke, if present, second kind result
 * 
 * \return depends of the parameter number
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace nt2 {
  namespace tag
  {
    /*!
     * \brief Define the tag ellipke_ of functor ellipke 
     *        in namespace nt2::tag for toolbox elliptic
    **/
    struct ellipke_ : ext::elementwise_<ellipke_> {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::ellipke_, ellipke, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::ellipke_, ellipke, 2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipke_, ellipke,(A0 const&)(A1&)(A2&),3)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipke_, ellipke,(A0 const&)(A1 const&)(A2&)(A3&),4)
}

#endif
