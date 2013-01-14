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
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SQRT1PM1_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SQRT1PM1_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>

/*!
 * \ingroup boost_math
 * \defgroup boost_math_sqrt1pm1 sqrt1pm1
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library boost_math.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/toolbox/boost_math/include/functions/sqrt1pm1.hpp>
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
 *       meta::call<tag::sqrt1pm1_(A0)>::type
 *       sqrt1pm1(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sqrt1pm1
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
     * \brief Define the tag sqrt1pm1_ of functor sqrt1pm1
     *        in namespace nt2::boost_math::tag for toolbox boost_math
    **/
    struct sqrt1pm1_ : ext::elementwise_<sqrt1pm1_> { typedef ext::elementwise_<sqrt1pm1_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(boost_math::tag::sqrt1pm1_, sqrt1pm1, 1)
  } }

#include <nt2/toolbox/boost_math/functions/scalar/sqrt1pm1.hpp>
// #include <nt2/toolbox/boost_math/functions/simd/all/sqrt1pm1.hpp>

#endif

// modified by jt the 29/12/2010
