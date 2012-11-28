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
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_PRIMES_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_PRIMES_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_primes primes
 *
 * \par Description
 * returns the table of prime numbers less or equal to the input
 * \par
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/primes.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class T,class A0>
 *     meta::call<tag::primes_(A0)>::type
 *     primes(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of primes
 *
 * \param T template parameter of primes
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
     * \brief Define the tag primes_ of functor primes
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct primes_ : ext::elementwise_<primes_> { typedef ext::elementwise_<primes_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::primes_,primes, 1)
}

#endif

