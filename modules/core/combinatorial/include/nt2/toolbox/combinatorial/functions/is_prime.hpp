/******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_IS_PRIME_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_IS_PRIME_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_is_prime is_prime
 *
 * \par Description
 * returns the table of prime numbers less or equal to the input
 * \par
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/is_prime.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::is_prime_(A0)>::type
 *     is_prime(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of is_prime
 *
 * \param T template parameter of is_prime
 *
 * \return a value of the template parameter type T.
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag is_prime_ of functor is_prime
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    //    struct is_prime_ : ext::elementwise_<is_prime_> { typedef ext::elementwise_<is_prime_> parent; };
    struct is_prime_ : tag::formal_{ typedef tag::formal_ parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::is_prime_,is_prime, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::is_prime_,is_prime, 2)
}

#endif

