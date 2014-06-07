//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NORM_fro_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NORM_fro_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_norm_fro norm_fro
 *
 * \par Description
 * compute the froboenius norm of a vector or a matrix
 *
 * that is :
 *  sqrt(asum2((_))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/norm_fro.hpp>
 * \endcode
 *
 *
 * norm_fro can be used as
 * norm_fro(a)
 *   or
 * norm_fro(a, nt2::vector_)
 *  or
 * norm_fro(a, nt2::matrix_)
 *
 * the second parameter is for shake of compatibility with morm_1 and norm_inf
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag norm_fro_ of functor norm_fro
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct norm_fro_ :  boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_fro_, norm_fro, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_fro_, norm_fro, 1)

}

#endif

