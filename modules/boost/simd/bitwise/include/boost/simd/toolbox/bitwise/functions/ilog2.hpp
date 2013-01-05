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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_ILOG2_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_ILOG2_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_ilog2 ilog2
 *
 * \par Description
 * The function return the integer part of log2 of the argument
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ilog2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::ilog2_(A0)>::type
 *     ilog2(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ilog2
 *
 * \return always returns an integer value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag ilog2_ of functor ilog2
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct ilog2_ : ext::elementwise_<ilog2_> { typedef ext::elementwise_<ilog2_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ilog2_, ilog2, 1)
} }

#endif

// modified by jt the 25/12/2010
