//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SELDEC_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SELDEC_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>

/*!
 * \ingroup boost_simd_boolean
 * \defgroup boost_simd_boolean_seldec seldec
 *
 * \par Description
 * Decrements a value by 1 if a predicate is true.
 *
 * \par Header file
 *
 * \code
 * #seldeclude <nt2/include/functions/seldec.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *   meta::call<tag::seldec_(A0, A1)>::type
 *   seldec(const A0 & a0, const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the condition that says whether to decrement
 * \param a1 the value to decrement
 *
 * \return a value of the same type as \c a1
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd {
  namespace tag
  {
    /*!
     * \brief Define the tag seldec_ of functor seldec
     *        in namespace boost::simd::tag for toolbox boost.simd.boolean
    **/
    struct seldec_ : ext::elementwise_<seldec_> { typedef ext::elementwise_<seldec_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::seldec_, seldec, 2)
} }

#endif
