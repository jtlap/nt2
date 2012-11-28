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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REC_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_REC_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_rec rec
 *
 * \par Description
 * return the inverse of the input as a floating point value.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rec.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::rec_(A0)>::type
 *     rec(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of rec
 *
 * \return always return floating point values
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag rec_ of functor rec
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct rec_ : ext::elementwise_<rec_> { typedef ext::elementwise_<rec_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rec_, rec, 1)
} }

#endif

// modified by jt the 25/12/2010
