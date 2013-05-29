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
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_IDIVROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_IDIVROUND2EVEN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_idivround2even idivround2even
 *
 * \par Description
 * return the \c round2even of the operands real divisionin the corresponding integer type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/idivround2even.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::idivround2even_(A0,A0)>::type
 *     idivround2even(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of idivround2even
 * \param a1 the second parameter of idivround2even
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
     * \brief Define the tag idivround2even_ of functor idivround2even
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct idivround2even_ : ext::elementwise_<idivround2even_> { typedef ext::elementwise_<idivround2even_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::idivround2even_, idivround2even, 2)
} }

#endif

// modified by jt the 25/12/2010
