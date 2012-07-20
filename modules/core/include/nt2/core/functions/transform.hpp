//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRANSFORM_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::transform function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct transform_ : tag::formal_ { typedef tag::formal_ parent; };
  }

  //============================================================================
  /*!
   * Evaluates all elements of \c a1, possibly in parallel,
   * and store the result in \c a0.
   *
   * \param a0 Expression to store result in
   * \param a1 Expression to evaluate
   * \param a2 Optional linear offset
   * \param a3 Optional number of element to process on the inner dimension
   * \param a4 Optional number of element to process on the outer dimension
   * \return nothing
   */
  //============================================================================
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::transform_, transform, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0 const&)(A1&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1&), 2)

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::transform_, transform, 5)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1 const&)(A2 const&)(A3 const&)(A4 const&), 5)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0 const&)(A1&)(A2 const&)(A3 const&)(A4 const&), 5)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1&)(A2 const&)(A3 const&)(A4 const&), 5)
}

#endif
