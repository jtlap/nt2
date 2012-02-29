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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FAST_TOINT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FAST_TOINT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_fast_toint fast_toint
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/fast_toint.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::fast_toint_(A0)>::type
 *     fast_toint(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of fast_toint
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
     * \brief Define the tag fast_toint_ of functor fast_toint 
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct fast_toint_ : ext::elementwise_<fast_toint_> { typedef ext::elementwise_<fast_toint_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_toint_, fast_toint, 1)
} }

#endif
