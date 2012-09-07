//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_CORE_FUNCTIONS_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FOLD_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the fold function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for fold functor
    **/
    struct fold_ : ext::unspecified_<fold_>
    {
      typedef ext::unspecified_<fold_> parent;
    };
  }

  /*!
    @brief Folds elements of an expression

    Perform a folding operation on an expression using the best algorithm
    depending on the curretn architecture backend.

    @param a0 Expression to fold
    @param a1 Functor to initialize the accumulator with
    @param a2 Function to apply for binary reduction, first argument is accumulator
    @param a3 Function to apply for unary reduction (for SIMD usage)
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::fold_, fold
                                            , (A0 const&)(A1 const&)
                                              (A2 const&)(A3 const&)
                                            , 4
                                            )

  /// INTERNAL ONLY
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::fold_, fold
                                            , (A0&)(A1 const&)
                                              (A2 const&)(A3 const&)
                                            , 4
                                            )
}

#endif
