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
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ADDS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ADDS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_arithmetic
 * \defgroup boost_simd_arithmetic_adds adds
 *
 * \par Description
 * The result is the mathetical adddition of the arguments
 * saturated in the interval defined by the common arguments type bounds
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/adds.hpp>
 * \endcode
 *
 * \par Alias
 * \arg saturated_add
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::adds_(A0,A0)>::type
 *     adds(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of adds
 * \param a1 the second parameter of adds
 *
 * \return a value of the common type of the parameters
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
     * \brief Define the tag adds_ of functor adds
     *        in namespace boost::simd::tag for toolbox boost.simd.arithmetic
    **/
    struct adds_ : ext::elementwise_<adds_> { typedef ext::elementwise_<adds_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::adds_, adds, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::adds_, saturated_add, 2)
} }

#endif
