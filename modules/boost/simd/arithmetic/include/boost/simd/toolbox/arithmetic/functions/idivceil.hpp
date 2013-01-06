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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IDIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IDIVCEIL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_idivceil idivceil
 *
 * \par Description
 * return the \c ceil of the operands real divisionin the corresponding integer type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/idivceil.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::idivceil_(A0,A0)>::type
 *     idivceil(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of idivceil
 * \param a1 the second parameter of idivceil
 *
 * \return an integer value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag idivceil_ of functor idivceil
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct idivceil_ : ext::elementwise_<idivceil_> { typedef ext::elementwise_<idivceil_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::idivceil_, idivceil, 2)
} }

#endif

// modified by jt the 25/12/2010
