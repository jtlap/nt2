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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_RSHL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_RSHL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_rshl rshl
 *
 * \par Description
 * The function returns the first entry shifted left or right
 * by the absolute value of second entry according to its sign.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rshl.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::rshl_(A0,A0)>::type
 *     rshl(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of rshl
 * \param a1 the second parameter of rshl, must be an integer value
 *
 * \return returns a value of the type of the first parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag rshl_ of functor rshl
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct rshl_ : ext::elementwise_<rshl_> { typedef ext::elementwise_<rshl_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rshl_, rshl, 2)
} }

#endif

// modified by jt the 25/12/2010
