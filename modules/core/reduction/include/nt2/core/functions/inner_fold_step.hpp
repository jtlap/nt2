//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_INNER_FOLD_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_INNER_FOLD_STEP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the inner_fold_step function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the inner_fold_step functor
    **/
    struct inner_fold_step_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief PreFold over inner dimension

    Folds elements of @c a1 along inner dimension, possibly in parallel, and
    store the result in @c a0.

    @param a0 Expression to store result in
    @param a1 Expression to reduce
    @param a2 Functor to initialize the accumulator with
    @param a3 Function to apply for binary reduction, first argument is accumulator
    @param a4 Linear offset
    @param a5 Begin of range
    @param a6 End of range
  **/

BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::inner_fold_step_, inner_fold_step,
(A0&)(A1 const&)(A2 const&)(A3 const&)(A4 const&), 5)
}

#endif
