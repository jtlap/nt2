//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NORM_INF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NORM_INF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_norm_inf norm_inf
 *
 * \par Description
 * compute the infinity norm of a vector or a matrix
 *
 * that is :
 *  max(abs(a)) for a vector
 *  max(sum(abs(a), 2)) for a matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/norm_inf.hpp>
 * \endcode
 *
 *
 * norm_inf can be used as
 * norm_inf(a)
 *   or
 * norm_inf(a, nt2::vector_)
 *  or
 * norm_inf(a, nt2::matrix_)
 *
 * the second parameter can be used to suppose with vector_ that a is a big column vector
 * or with matrix_ that it is a matrix
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag norm_inf_ of functor norm_inf
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct norm_inf_ :  boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_inf_, norm_inf, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_inf_, norm_inf, 1)

}

#endif

