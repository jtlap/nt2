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
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_NTHROOT_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_NTHROOT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_nthroot nthroot
 *
 * \par Description
 * nth root function: \f$\sqrt[a_1]{a_0}\f$
 * \par
 * \arg a1 must be of integer type
 * \arg if a1 is even and a0 negative the result is nan
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/nthroot.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::nthroot_(A0,A0)>::type
 *     nthroot(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of nthroot
 * \param a1 the second parameter of nthroot, must be of integer type
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
     * \brief Define the tag nthroot_ of functor nthroot
     *        in namespace nt2::tag for toolbox exponential
    **/
    struct nthroot_ : ext::elementwise_<nthroot_> { typedef ext::elementwise_<nthroot_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::nthroot_, nthroot, 2)
}

#endif

// modified by jt the 25/12/2010
