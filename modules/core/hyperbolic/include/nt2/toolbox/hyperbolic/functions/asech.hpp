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
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ASECH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_ASECH_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup hyperbolic
 * \defgroup hyperbolic_asech asech
 *
 * \par Description
 * hyperbolic secant argument \f$\mathop{\textrm{acosh}}(1/a_0)\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/asech.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::asech_(A0)>::type
 *     asech(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of asech
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
     * \brief Define the tag asech_ of functor asech
     *        in namespace nt2::tag for toolbox hyperbolic
    **/
    struct asech_ : ext::elementwise_<asech_> { typedef ext::elementwise_<asech_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::asech_, asech, 1)
}

#endif

// modified by jt the 25/12/2010
