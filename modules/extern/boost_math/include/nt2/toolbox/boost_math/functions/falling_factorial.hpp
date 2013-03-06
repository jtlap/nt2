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
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_FALLING_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_FALLING_FACTORIAL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/factorials.hpp>

/*!
 * \ingroup boost_math
 * \defgroup boost_math_falling_factorial falling_factorial
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library boost_math.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/boost_math/include/functions/falling_factorial.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace boost_math
 *   {
 *     template <class A0>
 *       meta::call<tag::falling_factorial_(A0,A0)>::type
 *       falling_factorial(const A0 & a0,const A0 & a1);
 *   }
 * }
 * \endcode
 *
 * \param a0 the first parameter of falling_factorial
 * \param a1 the second parameter of falling_factorial
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * When calling external library, nt2 simply encapsulates the
 * original proper call to provide easy use.
 * \par
 * Remenber that SIMD implementation is therefore merely
 * mapping the scalar function to each SIMD vectors elements
 * and will not provide acceleration, but ease.
 *
**/

namespace nt2 { namespace boost_math { namespace tag
  {
    /*!
     * \brief Define the tag falling_factorial_ of functor falling_factorial
     *        in namespace nt2::boost_math::tag for toolbox boost_math
    **/
    struct falling_factorial_ : ext::elementwise_<falling_factorial_> { typedef ext::elementwise_<falling_factorial_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(boost_math::tag::falling_factorial_, falling_factorial, 2)
  } }

#include <nt2/toolbox/boost_math/functions/scalar/falling_factorial.hpp>
// #include <nt2/toolbox/boost_math/functions/simd/all/falling_factorial.hpp>

#endif

// modified by jt the 29/12/2010
