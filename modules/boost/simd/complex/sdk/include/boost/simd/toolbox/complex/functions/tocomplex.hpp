//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_TOCOMPLEX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_TOCOMPLEX_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/complex/complex.hpp>

/*!
 * \ingroup boost_simd_complex
 * \defgroup boost_simd_complex_tocomplex tocomplex
 *
 * \par Description
 * return a complex from the argument
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/tocomplex.hpp>
 * \endcode
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::tocomplex_(A0)>::type
 *     tocomplex(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of tocomplex
 * 
 * \return a real value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the input vectors' elements
 * \par
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag tocomplex_ of functor tocomplex 
     *        in namespace boost::simd::tag for toolbox boost.simd.complex
    **/
    struct tocomplex_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tocomplex_, tocomplex, 1)
} }

#endif
