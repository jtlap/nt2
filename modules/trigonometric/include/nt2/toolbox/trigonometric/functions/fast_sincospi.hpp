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
 * \defgroup fast_sincospi fast_sincospi function
 *
 * \par Description
 * TODO Put description here
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
 *   template <class A0>
 *     meta::call<tag::fast_sincospi_(A0)>::type
 *     fast_sincospi(const A0 & a0);
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
     *        in namespace nt2::tag
    **/
    struct fast_sincospi_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincospi_, fast_sincospi, 1)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincospi_, fast_sincospi,(A0 const&)(A1&),2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincospi_, fast_sincospi,(A0 const&)(A1&)(A2&),3)
}

#endif

// modified by jt the 25/12/2010
