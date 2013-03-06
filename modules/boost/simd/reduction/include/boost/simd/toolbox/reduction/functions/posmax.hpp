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
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_POSMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_POSMAX_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_posmax posmax
 *
 * \par Description
 * Returns the index of the first occurence of greatest element of the SIMD vector
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/posmax.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::posmax_(A0)>::type
 *     posmax(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of posmax
 *
 * \return always a scalar value
 *
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag posmax_ of functor posmax
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct posmax_ : ext::unspecified_<posmax_> { typedef ext::unspecified_<posmax_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::posmax_, posmax, 1)
} }

#endif

// modified by jt the 25/12/2010
