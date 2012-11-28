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
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FRAC_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_FRAC_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_ieee
 * \defgroup boost_simd_ieee_frac frac
 *
 * \par Description
 * This function returns the fractional part of the input
 * that is \c a0-trunc(a0).
 * \par
 * This is always zero for integer inputs.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/frac.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::frac_(A0)>::type
 *     frac(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of frac
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
     * \brief Define the tag frac_ of functor frac
     *        in namespace boost::simd::tag for toolbox boost.simd.ieee
    **/
    struct frac_ : ext::elementwise_<frac_> { typedef ext::elementwise_<frac_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::frac_, frac, 1)
} }

#endif

// modified by jt the 25/12/2010
