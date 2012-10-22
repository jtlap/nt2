//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ARECROSSCOMPATIBLE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ARECROSSCOMPATIBLE_HPP_INCLUDED

/*!
  @file
  @brief Define the arecrosscompatible function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for arecrosscompatible functor
    **/
    struct arecrosscompatible_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Check for concrossenation compatibility

    For two given expressions and a given dimension, arecrosscompatible verifies
    that the concrossenation of both table along the chosen dimension is valid.

    @param a0  First expression to concrossenate
    @param a1  Second expression to concrossenate
    @param dim Dimension along which the concrossenation is tested

    @return a boolean value that evaluates to true if @c a0 and @c a1 can be
    concrossenated along thier @c dim dimension.
  **/
  template< class A0, class A1,class D>
  BOOST_FORCEINLINE
  typename meta::call<tag::arecrosscompatible_(A0 const&, A1 const&, D const&)>::type
  arecrosscompatible(A0 const& a0, A1 const& a1, D const& dim)
  {
    return typename make_functor<tag::arecrosscompatible_,A0>::type()(a0,a1,dim);
  }
}

#endif
