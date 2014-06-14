//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORM_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnorm mnorm
 *
 * \par Description
 * compute the 2 norm of a  matrix ie the largest singular value of the matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnorm.hpp>
 * \endcode
 *
 *
 * mnorm can be used as
 * mnorm(a)
 *   or
 * mnorm(a, nt2::vector_)
 *  or
 * mnorm(a, nt2::matrix_)
 *
 * the second parameter can be used to suppose with vector_ that a is a big column vector
 * or with matrix_ that it is a matrix
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnorm_ of functor mnorm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct mnorm_ :  boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm_, mnorm2, 1)

}

#endif

