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
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_REVERSE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_reverse reverse
 *
 * \par Description
 * returns a vector the elements of which are
 * those of a0 in reverse order
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/reverse.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::reverse_(A0)>::type
 *     reverse(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the  parameter of reverse
 *
 * \return a value of the common type of the parameters
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
     * \brief Define the tag reverse_ of functor reverse
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct reverse_ : ext::unspecified_<reverse_> { typedef ext::unspecified_<reverse_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::reverse_, reverse, 1)
} }

#endif


