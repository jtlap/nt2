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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_POWI_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_POWI_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_powi powi
 *
 * \par Description
 * Power function for scalar integer a1: ${a_0}^{a_1}$
 * \par
 * $0^0$ returns 1
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/powi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::powi_(A0,A0)>::type
 *     powi(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of powi
 * \param a1 the second parameter of powi, must be of scalar integer type
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag powi_ of functor powi
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct powi_ : ext::elementwise_<powi_> { typedef ext::elementwise_<powi_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::powi_, powi, 2)
}

#endif

// modified by jt the 25/12/2010
