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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SPLATTED_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SPLATTED_SUM_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_splatted_sum splatted_sum
 *
 * \par Description
 * returns the sum of a0 elements splatted in a vector
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/splatted_sum.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::splatted_sum_(A0)>::type
 *     splatted_sum(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of splatted_sum
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
     * \brief Define the tag splatted_sum_ of functor splatted_sum
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct splatted_sum_ : ext::unspecified_<splatted_sum_> { typedef ext::unspecified_<splatted_sum_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_sum_, splatted_sum, 1)
} }

#endif

// modified by jt the 25/12/2010
