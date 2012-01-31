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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SQRT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SQRT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_sqrt sqrt
 *
 * \par Description
 * return a floating point value which is the square root of the entry
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/sqrt.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sqrt_(A0)>::type
 *     sqrt(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sqrt
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag sqrt_ of functor sqrt 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct sqrt_ : ext::elementwise_<sqrt_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqrt_, sqrt, 1)
} }

#endif

// modified by jt the 25/12/2010
