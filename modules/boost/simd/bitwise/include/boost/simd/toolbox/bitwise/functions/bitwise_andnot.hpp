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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_BITWISE_ANDNOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_bitwise_andnot bitwise_andnot
 *
 * \par Description
 * return the bitwise and of the first parameter
 * with the bitwise complement of the second parameter.
 * \par
 * The operands must share the same bit size and
 * the result type is the one of the first operand
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bitwise_andnot.hpp>
 * \endcode
 *
 * \par Alias
 * \arg b_andnot
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1>
 *     meta::call<tag::bitwise_andnot_(A0,A1)>::type
 *     bitwise_andnot(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of bitwise_andnot
 * \param a1 the second parameter of bitwise_andnot
 *
 * \return a value of the type of the first parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag bitwise_andnot_ of functor bitwise_andnot
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct bitwise_andnot_ : ext::elementwise_<bitwise_andnot_> { typedef ext::elementwise_<bitwise_andnot_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_andnot_, bitwise_andnot, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_andnot_, b_andnot, 2)
} }

#endif
