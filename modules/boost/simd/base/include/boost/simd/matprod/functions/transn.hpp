//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_TRANSN_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_TRANSN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief transn generic tag

     Represents the transn function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct transn_ : ext::elementwise_<transn_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<transn_> parent;
    };
  }
  /*!
    returns the transpose matrix product of
         an NxN  matrix represented by an array of N simd vector of cardinal N

    transn(a)


    @param a a boost::array of N simd vectors where N is the cardinal of an simd vector

    @return an array of vector of the same type as a but containing the transpose
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::transn_, transn, 1 )
} }



#endif
