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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_HI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_HI_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_hi hi
 *
 * \par Description
 * The function returns the high part of the entry
 * shifted right as an integer of the same size as
 * the input.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/hi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::hi_(A0)>::type
 *     hi(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of hi
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
     * \brief Define the tag hi_ of functor hi
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct hi_ : ext::elementwise_<hi_> { typedef ext::elementwise_<hi_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hi_, hi, 1)
} }

#endif

// modified by jt the 25/12/2010
