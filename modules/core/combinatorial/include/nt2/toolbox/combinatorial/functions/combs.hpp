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
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_COMBS_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_COMBS_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_combs combs
 *
 * \par Description
 *   combs(n,k) where n and k are non-negative integers returns n!/k!(n-k)!.
 *   this is the number of combinations of n things taken k at a time.
 *   when a coefficient is large, a warning will be produced indicating
 *   possible inexact results. in such cases, the result is only accurate
 *   to 15 digits for double-precision inputs, or 8 digits for single-precision
 *   inputs.
 *
 *   combs(v,k) where v is a vector of length n, produces a matrix
 *   with n!/k!(n-k)! rows and k columns. each row of the result has k of
 *   the elements in the vector v. this syntax is only practical for
 *   situations where n is less than about 15.
 *
 *
 * \code
 * #include <nt2/include/functions/combs.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::combs_(A0,A0)>::type
 *     combs(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of combs
 * \param a1 the second parameter of combs
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
     * \brief Define the tag combs_ of functor combs
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct combs_ : ext::elementwise_<combs_> { typedef ext::elementwise_<combs_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::combs_, combs, 2)
}

#endif

// modified by jt the 25/12/2010
