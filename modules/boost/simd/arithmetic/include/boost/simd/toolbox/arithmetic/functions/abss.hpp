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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ABSS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ABSS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_abss abss
 *
 * \par Description
 * This is generally equivalent to abs except for signed integer
 * types for which \c abss(Valmin) is \c Valmax-1
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/abss.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg sturated_abs
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::abss_(A0)>::type
 *     abss(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of abss
 * 
 * \return a value of the same type as the parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *  
**/

namespace boost { namespace simd {
  namespace tag
  {
    /*!
     * \brief Define the tag abss_ of functor abss 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct abss_ : ext::elementwise_<abss_>{};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abss_, abss, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abss_, sturated_abs, 1)
} }

#endif
