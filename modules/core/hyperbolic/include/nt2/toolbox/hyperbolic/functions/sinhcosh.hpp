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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SINHCOSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SINHCOSH_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_sinhcosh sinhcosh
 *
 * \par Description
 * simultaneous sine and cosine.
 * \arg tie(si,co) = sinhcosh(a) returns the hyperbolic sin and cosin of a.
 * \arg si = sinhcosh(a,co) returns the hyperbolic sine of a and put the cosine of a in co.
 * \arg sinhcosh(a,si,co) returns 0 and and put the hyperbolic sine of a in si and the cosine cosine of a in co.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sinhcosh.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template<class A0> inline
 *   typename boost::dispatch::meta::call<tag::sinhcosh(A0 const&,A0 const&)
 *                                       >::type
 *   sinhcosh(A0 const& a);
 *    
 *   template<class A0> inline
 *   A0 sinhcosh(A0 const& a,A0,A0& si);
 *    
 *   template<class A0> inline
 *   int sinhcosh(A0 const& a,A0,A0& si,A0& co);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sinhcosh
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
     * \brief Define the tag sinhcosh_ of functor sinhcosh 
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct sinhcosh_ : ext::elementwise_<sinhcosh_> { typedef ext::elementwise_<sinhcosh_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::sinhcosh_, sinhcosh, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sinhcosh,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sinhcosh,(A0 const&)(A1&)(A2&),3)

}

#endif

// modified by jt the 25/12/2010
