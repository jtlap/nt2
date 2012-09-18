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
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_DOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_DOT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_dot dot
 *
 * \par Description
 * returns the dot product of the two SIMD vector arguments
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/dot.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::dot_(A0,A0)>::type
 *     dot(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of dot
 * \param a1 the second parameter of dot
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
     * \brief Define the tag dot_ of functor dot
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct dot_ : ext::unspecified_<dot_> { typedef ext::unspecified_<dot_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::dot_, dot, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::dot_, dot, 3)
} }

#endif
