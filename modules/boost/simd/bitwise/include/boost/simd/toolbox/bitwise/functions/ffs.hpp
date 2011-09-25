//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_bitwise
 * \defgroup ffs ffs function
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
 * \param a0 is the unique parameter of ffs
 * 
 * \return always returns an integer value
 *  
 * \internal end_functor \endinternal
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \internal tag \endinternal
     * \file
     * \brief Define the tag ffs_ of functor ffs 
     *        in namespace boost::simd::tag
     * \internal end_tag \endinternal
    **/
    struct ffs_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ffs_, ffs, 1)
} }

#endif

// modified by jt the 25/12/2010
