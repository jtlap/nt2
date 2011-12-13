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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_GENMASK_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_genmask genmask
 *
 * \par Description
 * The function returns a mask of bits. All ones if the
 * input element is non zero else all zeros
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/genmask.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg typed_mask
 * \arg logical2mask
 * \arg l2m
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::genmask_(A0)>::type
 *     genmask(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of genmask
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
     * \brief Define the tag genmask_ of functor genmask 
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct genmask_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, genmask, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, typed_mask, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, logical2mask, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmask_, l2m, 1)
} }

#endif

// modified by jt the 25/12/2010
