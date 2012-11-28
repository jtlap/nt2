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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVROUND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVROUND_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_divround divround
 *
 * \par Description
 * return the \c round of the operands real divisionin the input type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/divround.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::divround_(A0,A0)>::type
 *     divround(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of divround
 * \param a1 the second parameter of divround
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
     * \brief Define the tag divround_ of functor divround
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct divround_ : ext::elementwise_<divround_> { typedef ext::elementwise_<divround_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divround_, divround, 2)
} }

#endif
