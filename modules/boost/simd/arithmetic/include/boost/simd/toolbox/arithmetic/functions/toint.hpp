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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TOINT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_TOINT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_toint toint
 *
 * \par Description
 * convert an entry to integer by truncation.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/toint.hpp>
 * \endcode
 *
 * \par Aliases
 * \arg ifix
 * \arg itrunc
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::toint_(A0)>::type
 *     toint(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of toint
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
     * \brief Define the tag toint_ of functor toint
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct toint_ : ext::elementwise_<toint_> { typedef ext::elementwise_<toint_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, toint, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, ifix, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, itrunc, 1)
} }

#endif

// modified by jt the 25/12/2010
