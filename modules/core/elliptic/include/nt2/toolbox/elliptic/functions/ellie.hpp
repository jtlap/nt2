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
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLIE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_ELLIE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup elliptic
 * \defgroup elliptic_ellie ellie
 *
 * \par Description
 * Incomplete elliptic integral of the second kind
 * \par Formula
 * \f[E(a_0,a_1) = \int_0^{a0} \sqrt{1-a_1\sin^2 t} dt\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ellie.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::ellie_(A0,A0)>::type
 *     ellie(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of ellie
 * \param a1 the second parameter of ellie
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
     * \brief Define the tag ellie_ of functor ellie
     *        in namespace nt2::tag for toolbox elliptic
    **/
    struct ellie_ : ext::elementwise_<ellie_> { typedef ext::elementwise_<ellie_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::ellie_, ellie, 2)
}

#endif

// modified by jt the 25/12/2010
