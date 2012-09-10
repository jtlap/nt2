//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DOT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DOT_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the dot function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the dot functor
    **/
    struct dot_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Dot product between expressions

    Comput the dot product of two expressions along their first non-singleton
    dimension.

    @param a0 First expression to process
    @param a1 Second expression to process

    @return The dot product of a0 and a1 along their first non-singleton
    dimension
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::dot_, dot, 2)

  /*!
    @brief Dot product between expressions along a dimension

    Comput the dot product of two expressions along a specified simension
    dimension.

    @param a0 First expression to process
    @param a1 Second expression to process
    @param a2 Dimension to ptocess

    @return The dot product of a0 and a1 along the dimension specified in a2
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::dot_, dot, 3)
}

#endif
