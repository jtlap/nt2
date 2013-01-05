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
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_IS_SIMD_LOGICAL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_reduction
 * \defgroup boost_simd_reduction_is_simd_logical is_simd_logical
 *
 * \par Description
 * returns true if all vector elements have all or no bit sets.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/is_simd_logical.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_simd_logical_(A0)>::type
 *     is_simd_logical(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of is_simd_logical
 *
 * \return an integer value
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
     * \brief Define the tag is_simd_logical_ of functor is_simd_logical
     *        in namespace boost::simd::tag for toolbox boost.simd.reduction
    **/
    struct is_simd_logical_ : ext::unspecified_<is_simd_logical_>
    {
      typedef ext::unspecified_<is_simd_logical_> parent;
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_simd_logical_, is_simd_logical, 1)
} }

#endif
