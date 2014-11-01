//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_MUL_NTP_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_MUL_NTP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief mul_ntp generic tag

     Represents the mul_ntp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct mul_ntp_ : ext::elementwise_<mul_ntp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mul_ntp_> parent;
    };
  }
  /*!
    returns the matrix product of
          an NxN matrix a represented by an array of N simd vector of cardinal N
       by the transpose of a PxN matrix b represented by an array of P simd vector of cardinal N ( 0 < P and P static)

    simd vectors represent columns of a and of the result and lines of b

    for sse2 this means 2x2 * trans(Px2)  for double elements
                        4x4 * trans(Px4)  for float elements
    for avx this means  4x4 * trans(Px4)  for double elements
                        8x8 * trans(Px8)  for float elements

    If * is an hypothetical matrix product between a and b, and alpha and beta are scalars

    r = mul_ntp(a, b)              is equivalent to r = a*tb
    mul_ntp(a, b, r)               is equivalent to r += a*tb
    mul_ntp(alpha, a, b, r)        is equivalent to r += alpha*a*tb
    mul_ntp(alpha, a, b, beta, r ) is equivalent to r = beta*r+alpha*a*tb

    @param a a boost::array of N simd vectors where N is the cardinal of an simd vector

    @param b a boost::array of P simd vectors

    @return a matrix of the same type as b
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mul_ntp_, mul_ntp, 2 )
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_ntp_, mul_ntp,(A0 const&)(A1 const&)(A2 &),3)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_ntp_, mul_ntp,(A0 const&)(A1 const&)(A2 const&)(A3 &),4)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_ntp_, mul_ntp,(A0 const&)(A1 const&)(A2 const&)(A3 const&)(A4 &),5)
} }



#endif
