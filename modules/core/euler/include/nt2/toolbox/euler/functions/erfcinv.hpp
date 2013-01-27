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
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_ERFCINV_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_ERFCINV_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_erfcinv erfcinv
 *
 * \par Description
 * erfcinv function
 * inverse of erfc
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/erfcinv.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::erfcinv_(A0)>::type
 *     erfcinv(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of erfcinv
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
     * \brief Define the tag erfcinv_ of functor erfcinv
     *        in namespace nt2::tag for toolbox euler
    **/
    struct erfcinv_ : ext::elementwise_<erfcinv_> { typedef ext::elementwise_<erfcinv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::erfcinv_, erfcinv, 1)
}

#endif

// modified by jt the 25/12/2010
