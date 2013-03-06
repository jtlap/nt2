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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_CUMSUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_CUMSUM_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/operator/functions/plus.hpp>
#include <boost/simd/toolbox/constant/constants/zero.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_cumsum cumsum
 *
 * \par Description
 * compute the cumulate sum of the vector elements
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cumsum.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::cumsum_(A0)>::type
 *     cumsum(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cumsum
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * \par
 * This is a swar operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation is a transform of an SIMD vector, that will return
 * vectors obtained on a non necessarily elementwise basis from the inputs
 * elements
 * \par
 * If usable and used in scalar mode, it reduces to the operation
 * on a one element vector.
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag cumsum_ of functor cumsum
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct cumsum_ : ext::cumulative_<cumsum_, tag::plus_, tag::Zero>
    {
      typedef ext::cumulative_<cumsum_, tag::plus_, tag::Zero> parent;
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumsum_, cumsum, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumsum_, cumsum, 2)
} }

#endif

// modified by jt the 25/12/2010
