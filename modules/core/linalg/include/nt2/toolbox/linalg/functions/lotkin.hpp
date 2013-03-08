/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_LOTKIN_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_LOTKIN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_lotkin lotkin
 *
 *    lotkin(a,b) is the n-by-n matrix from the Lotkin
 *    population model with average birth numbers a(_(1, n)) and
 *    survival rates b(_(1, n-1)).  it is zero, apart from on the first row
 *    (which contains the a(i)) and the first subdiagonal (which contains
 *    the b(i)).  for a valid model, the a(i) are nonnegative and the
 *    b(i) are positive and bounded by 1.
 *
 *    lotkin(n) generates the lotkin matrix with a = ones(n,1),
 *    b = ones(n-1,1).

 *    References:
 *    [1] M. R. Cullen, Linear Models in Biology, Ellis Horwood,
 *        Chichester, UK, 1985.
 *    [2] H. Anton and C. Rorres, Elementary Linear Algebra: Applications
 *        Version, eighth edition, Wiley, New York, 2000, Sec. 11.18.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lotkin.hpp>
 * \endcode
 *
 **/
//==============================================================================
// lotkin actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lotkin_ of functor lotkin
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lotkin_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lotkin_, lotkin, 2)

}

#endif

