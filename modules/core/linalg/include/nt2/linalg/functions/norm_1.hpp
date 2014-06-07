//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NORM_1_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NORM_1_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_norm_1 norm_1
 *
 * \par Description
 * compute the 1-norm of a vector or a matrix
 *
 * that is :
 *  sum(abs(a)) for a vector
 *  max(sum(abs(a), 1)) for a matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/norm_1.hpp>
 * \endcode
 *
 *
 * norm_1 can be used as
 * norm_1(a)
 *   or
 * norm_1(a, nt2::vector_)
 *  or
 * norm_1(a, nt2::matrix_)
 *
 * the second parameter can be used to suppose with vector_ that a is a big column vector
 * or with matrix_ that it is a matrix
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag norm_1_ of functor norm_1
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct norm_1_ :  boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_1_, norm_1, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_1_, norm_1, 1)

}

#endif

