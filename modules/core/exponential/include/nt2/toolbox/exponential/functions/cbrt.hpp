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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_CBRT_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_CBRT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_cbrt cbrt
 *
 * \par Description
 * Cubic root: \f$\sqrt[3]{a_0}\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cbrt.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::cbrt_(A0)>::type
 *     cbrt(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cbrt
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
     * \brief Define the tag cbrt_ of functor cbrt
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct cbrt_ : ext::elementwise_<cbrt_> { typedef ext::elementwise_<cbrt_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::cbrt_, cbrt, 1)
}

#endif

// modified by jt the 25/12/2010
