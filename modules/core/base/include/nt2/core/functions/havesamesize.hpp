//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HAVESAMESIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HAVESAMESIZE_HPP_INCLUDED

/*!
  @file
  @brief Defines the havesamesize function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the havesamesize functor
    **/
    struct havesamesize_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Does two expression have the same size

    For two expression a0 and a1, checks is they have the same size.

    @param a0 First expression to compare
    @param a1 Second expression to compare

    @return Boolean value evaluating to the result of the test
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::havesamesize_, havesamesize, 2)
}

#endif
