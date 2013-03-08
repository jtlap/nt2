/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_MOLER_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_MOLER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_moler moler
 *
 * moler  moler matrix (symmetric positive definite).
 *    a = moler(n,alpha) is the symmetric positive definite
 *    n-by-n matrix u'*u, where u = triw(n,n,alpha).
 *
 *    for the default alpha = -1, a(i,j) = min(i,j)-2, and a(i,i) = i.
 *    one of the eigenvalues of a is small.
 *
 *    Nash [1] attributes the alpha = -1 matrix to Moler.
 *
 *    Reference:
 *    [1] J. C. Nash, Compact Numerical Methods for Computers: Linear
 *    Algebra and Function Minimisation, second edition, Adam Hilger,
 *    Bristol, 1990 (Appendix 1).
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/moler.hpp>
 * \endcode
 *
 **/
//==============================================================================
// moler actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag moler_ of functor moler
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct moler_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::moler_, moler, 2)

}

#endif

