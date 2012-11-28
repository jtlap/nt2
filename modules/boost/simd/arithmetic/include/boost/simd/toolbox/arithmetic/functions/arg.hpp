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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ARG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ARG_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_arg arg
 *
 * \par Description
 * The result is the argument of the input
 * Always return a floating point value
 * Always 0 or \f$\pi\f$ according to the input sign
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/arg.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::arg_(A0)>::type
 *     arg(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of arg
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
     * \brief Define the tag arg_ of functor arg
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct arg_ : ext::elementwise_<arg_> { typedef ext::elementwise_<arg_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::arg_, arg, 1)
} }

#endif

// modified by jt the 25/12/2010
