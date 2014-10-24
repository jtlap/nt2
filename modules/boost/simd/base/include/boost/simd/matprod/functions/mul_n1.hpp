//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_MUL_N1_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_MUL_N1_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief mul_n1 generic tag

     Represents the mul_n1 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct mul_n1_ : ext::elementwise_<mul_n1_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mul_n1_> parent;
    };
  }
  /*!
    returns the matrix product of
         an NxN matrix represented by an array of N simd vector of cardinal N
      by a simd vector of cardinal N.
    simd vectors represent columns

    for sse2 this means 2x2 * 2x1 for double elements
                        4x4 * 4x1 for float elements
    for avx this means  4x4 * 4x1 for double elements
                        8x8 * 8x1 for float elements

    If * is an hypothetical matrix product between a and b, and alpha and beta are scalars

    r = mul_n1(a, v)              is equivalent to r =  a*v
    mul_n1(a, v, r)               is equivalent to r += a*v
    mul_n1(alpha, a, v, r)        is equivalent to r += alpha*a*v
    mul_n1(alpha, a, v, beta, r ) is equivalent to r = beta*r+alpha*a*v

    @param a a boost::array of N simd vectors where N is the cardinal of an simd vector

    @param v an simd vector

    @return a vector of the same type as v
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mul_n1_, mul_n1, 2 )
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_n1_, mul_n1,(A0 const&)(A1 const&)(A2 &),3)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_n1_, mul_n1,(A0 const&)(A1 const&)(A2 const&)(A3 &),4)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_n1_, mul_n1,(A0 const&)(A1 const&)(A2 const&)(A3 const&)(A4 &),5)
} }



#endif
