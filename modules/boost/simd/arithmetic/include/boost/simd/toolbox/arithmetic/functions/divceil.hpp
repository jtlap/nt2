//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVCEIL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_divceil divceil
 *
 * \par Description
 * return the \c ceil of the operands real divisionin the input type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/divceil.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::divceil_(A0,A0)>::type
 *     divceil(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of divceil
 * \param a1 the second parameter of divceil
 *
 * \return a value of the common type of the parameters
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
     * \brief Define the tag divceil_ of functor divceil
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct divceil_ : ext::elementwise_<divceil_> { typedef ext::elementwise_<divceil_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divceil_, divceil, 2)
} }

#endif
