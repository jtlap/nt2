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
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_DOUBLE_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_DOUBLE_FACTORIAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <nt2/toolbox/boost_math/specific/interface.hpp>

/*!
 * \ingroup boost_math
 * \defgroup boost_math_double_factorial double_factorial
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library boost_math.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/boost_math/include/functions/double_factorial.hpp>
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
 *     template <class T,class A0>
 *       meta::call<tag::double_factorial_(A0)>::type
 *       double_factorial(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of double_factorial
 *
 * \return a value of the same type as the parameter
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
     * \brief Define the tag double_factorial_ of functor double_factorial
     *        in namespace nt2::boost_math::tag for toolbox boost_math
    **/
    template <class T> struct double_factorial_ : ext::elementwise_< double_factorial_<T> > { typedef ext::elementwise_< double_factorial_<T> > parent; };
  }
  NT2_BOOST_MATH_FUNCTION_IMPLEMENTATION_TPL(double_factorial,1)
  } }

#include <nt2/toolbox/boost_math/functions/scalar/double_factorial.hpp>

#endif

// modified by jt the 29/12/2010
