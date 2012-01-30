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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOSPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOSPI_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_fast_sincospi fast_sincospi
 *
 * \par Description
 * simultaneous sine and cosine from angle in \f$\pi\f$ multiples
 * in the interval \f$[-1/4,1/45]\f$, nan outside.
 * \arg tie(si,co) = fast_sincospi(a) returns the sine and cosine of a.
 * \arg si = fast_sincospi(a,co) returns the sine of a and put the cosine of a in co.
 * \arg fast_sincospi(a,si,co) returns 0 and and put the sine of a in si and the cosine cosine of a in co.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fast_sincospi.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::fast_sincospi(A0 const&,A0 const&)
 *                                       >::type
 *   fast_sincospi(A0 const& a);
 *    
 *   template<class A0> inline
 *   A0 fast_sincospi(A0 const& a,A0,A0& si);
 *    
 *   template<class A0> inline
 *   int fast_sincospi(A0 const& a,A0,A0& si,A0& co);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_sincospi
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
     * \brief Define the tag fast_sincospi_ of functor fast_sincospi 
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    struct fast_sincospi_ : ext::elementwise_<fast_sincospi_> {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincospi_, fast_sincospi, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincospi_, fast_sincospi,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincospi_, fast_sincospi,(A0 const&)(A1&)(A2&),3)
}

#endif

// modified by jt the 25/12/2010
