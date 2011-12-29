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
#ifndef BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_FROMPOLAR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_COMPLEX_FUNCTIONS_FROMPOLAR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/complex/complex.hpp>

/*!
 * \ingroup boost_simd_complex
 * \defgroup boost_simd_complex_frompolar frompolar
 *
 * \par Description
 * return a complex from the modulus and argument
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/frompolar.hpp>
 * \endcode
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::frompolar_(A0, A0)>::type
 *     frompolar(const A0 & a0, const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of frompolar
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
     * \brief Define the tag frompolar_ of functor frompolar 
     *        in namespace boost::simd::tag for toolbox boost.simd.complex
    **/
    struct frompolar_ {};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::frompolar_, frompolar, 2)
} }

#endif
