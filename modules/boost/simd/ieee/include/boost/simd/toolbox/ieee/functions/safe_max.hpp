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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SAFE_MAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SAFE_MAX_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_safe_max safe_max
 *
 * \par Description
 * Returns the safe_max relative to abs(a0),  ie the maximal
 * value which will not overflow when multiplied by a0.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/safe_max.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::safe_max_(A0)>::type
 *     safe_max(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of safe_max
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
     * \brief Define the tag safe_max_ of functor safe_max 
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct safe_max_ : ext::elementwise_<safe_max_> { typedef ext::elementwise_<safe_max_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::safe_max_, safe_max, 1)
} }

#endif

// modified by jt the 25/12/2010
