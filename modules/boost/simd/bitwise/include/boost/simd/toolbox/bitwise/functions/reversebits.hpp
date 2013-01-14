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
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_REVERSEBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_bitwise
 * \defgroup boost_simd_bitwise_reversebits reversebits
 *
 * \par Description
 * The function returns the bits of the entry in reverse order,
 * in the same type as the entry
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/reversebits.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::reversebits_(A0)>::type
 *     reversebits(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of reversebits
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag reversebits_ of functor reversebits
     *        in namespace boost::simd::tag for toolbox boost.simd.bitwise
    **/
    struct reversebits_ : ext::elementwise_<reversebits_> { typedef ext::elementwise_<reversebits_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::reversebits_, reversebits, 1)
} }

#endif

// modified by jt the 25/12/2010
