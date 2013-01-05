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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MINMOD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_MINMOD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_minmod minmod
 *
 * \par Description
 * return the minimum of the two entries
 *  if they have the same sign, otherwise 0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/minmod.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::minmod_(A0,A0)>::type
 *     minmod(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of minmod
 * \param a1 the second parameter of minmod
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag minmod_ of functor minmod
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct minmod_ : ext::elementwise_<minmod_> { typedef ext::elementwise_<minmod_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minmod_, minmod, 2)
} }

#endif

// modified by jt the 25/12/2010
