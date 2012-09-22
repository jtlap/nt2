//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HORZCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HORZCAT_HPP_INCLUDED

/*!
  @file
  @brief Define the horzcat function
**/
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the horzcat function
    **/
    struct  horzcat_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Horizontal concatenation

    Build a new expression which is the horizontal concatenation of all
    elements of a0 and a1.

    @param a0 First expression to concatenate
    @param a1 Second (optionnal) expression to concatenate

    @return An expression epresenting the concatenation of a0 and a1.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, horzcat, 2)

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, horzcat, 1)

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, cath, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, cath, 2)
}

#endif
