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
#ifndef BOOST_SIMD_TOOLBOX_COMPLEX_CONSTANTS_I_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_COMPLEX_CONSTANTS_I_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_complex
 * \defgroup boost_simd_complex_i I
 *
 * \par Description
 * Constant I : Imaginary unit.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/i.hpp>
 * \endcode
 *
 * \alias:
 *    J
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T>
 *     meta::call<tag::I(as_<T>)>::type
 *     I();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of I
 * 
 * \return type T value
 *  
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag I of functor I 
     *        in namespace boost::simd::tag for toolbox boost.simd.complex
    **/
    struct I 
    {
      typedef imaginary<double> default_type; 
    };
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::I, I)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::I, J)
} }

#endif
