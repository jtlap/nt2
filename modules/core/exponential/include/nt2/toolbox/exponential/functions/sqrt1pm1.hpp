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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SQRT1PM1_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SQRT1PM1_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_sqrt1pm1 sqrt1pm1
 *
 * \par Description
 * \f$\sqrt{1+a_0}-1\f$
 * \par
 * result is accurate even for small a0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrt1pm1.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::sqrt1pm1_(A0)>::type
 *     sqrt1pm1(const A0 & a0);
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
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag sqrt1pm1_ of functor sqrt1pm1
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct sqrt1pm1_ : ext::elementwise_<sqrt1pm1_> { typedef ext::elementwise_<sqrt1pm1_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::sqrt1pm1_, sqrt1pm1, 1)
}

#endif

// modified by jt the 25/12/2010
