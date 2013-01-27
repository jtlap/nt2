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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_ERF_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_ERF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_erf erf
 *
 * \par Description
 * Erf function
 * \par Formula
 * \f[ erf(x)=\frac{2}{\sqrt\pi}(\int_0^x exp(-t2)}dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/erf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::erf_(A0)>::type
 *     erf(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of erf
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
     * \brief Define the tag erf_ of functor erf
     *        in namespace nt2::tag for toolbox euler
    **/
    struct erf_ : ext::elementwise_<erf_> { typedef ext::elementwise_<erf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::erf_, erf, 1)
}

#endif

// modified by jt the 25/12/2010
