//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_TRANSHN_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_TRANSHN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief transhn generic tag

     Represents the transhn function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct transhn_ : ext::elementwise_<transhn_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<transhn_> parent;
    };
  }
  /*!
    returns the transpose matrix product of
         an (N*2)x(N/2) or((N/2)x(N*2))  matrix represented by an array of N simd vector of cardinal N

    ta = transhn(a)


    @param a a boost::array of N simd vectors where N is the cardinal of an simd vector

    @return an array of vector of the same type as a but containing the transpose
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::transhn_, transhn, 1 )
} }



#endif
