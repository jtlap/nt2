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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IFLOOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_IFLOOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_ifloor ifloor
 *
 * \par Description
 * return a value of integer type of the same size and signedness than the entry.
 * The value returned is the greatest integer less or equal than the entry
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ifloor.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::ifloor_(A0)>::type
 *     ifloor(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ifloor
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
     * \brief Define the tag ifloor_ of functor ifloor
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct ifloor_ : ext::elementwise_<ifloor_> { typedef ext::elementwise_<ifloor_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifloor_, ifloor, 1)
} }

#endif

// modified by jt the 25/12/2010
