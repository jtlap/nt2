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
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_TANGENT_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_TANGENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup trigonometric
 * \defgroup trigonometric_tangent tangent
 *
 * \par Description
 * tangent.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tangent.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::tangent_(A0)>::type
 *     tangent(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of tangent
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
     * \brief Define the tag tangent_ of functor tangent
     *        in namespace nt2::tag for toolbox trigonometric
    **/
    template <class T> struct tangent_ : ext::elementwise_< tangent_<T> > { typedef ext::elementwise_< tangent_<T> > parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::tangent_<A0> , tangent, (A1 const&), 2)
}

#endif

// modified by jt the 25/12/2010
