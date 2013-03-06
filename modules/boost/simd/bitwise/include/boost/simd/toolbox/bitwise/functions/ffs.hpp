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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_ffs ffs
 *
 * \par Description
 * The function finds the first bit set (beginning with the least
 * significant bit) in a0, and return the index of that bit.
 * \par
 * Bits are numbered starting at one (the least significant bit).
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ffs.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::ffs_(A0)>::type
 *     ffs(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of ffs
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
     * \brief Define the tag ffs_ of functor ffs
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct ffs_ : ext::elementwise_<ffs_> { typedef ext::elementwise_<ffs_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ffs_, ffs, 1)
} }

#endif

// modified by jt the 25/12/2010
