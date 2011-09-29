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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOS_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup fast_sincos fast_sincos function
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fast_sincos.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fast_sincos_(A0)>::type
 *     fast_sincos(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_sincos
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
     * \brief Define the tag fast_sincos_ of functor fast_sincos 
     *        in namespace nt2::tag
    **/
    struct fast_sincos_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincos_, fast_sincos, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincos_, fast_sincos,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincos_, fast_sincos,(A0 const&)(A1&)(A2&),3)
}

#endif

// modified by jt the 25/12/2010
