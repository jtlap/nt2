//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_MUL_HN_2P_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_MUL_HN_2P_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief mul_hn_2p generic tag

     Represents the mul_hn_2p function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct mul_hn_2p_ : ext::elementwise_<mul_hn_2p_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mul_hn_2p_> parent;
    };
  }
  /*!
    returns the matrix product of
         an (N/2)x(2*N) matrix represented by an array of N simd vector of cardinal N
      by a  (2*N)x(2*P)   matrix represented by an array of 4 simd vectors of cardinal N
      to return a (N/2)x(2*P) matrix represented by an array of P simd vector of cardinal N.
    simd vectors represent columns

    for sse2 this means 1x4  * 4x(2*P)  for double elements as cardinal is 2
                        2x8  * 8x(2*P)  for float elements  as cardinal is 4
    for avx this means  2x8  * 8(x2*P)  for double elements as cardinal is 4
                        4x16 * 16x(2*P) for float elements  as cardinal is 8


    If * is an hypothetical matrix product between a and b, and alpha and beta are scalars

    r = mul_hn_2p(a, b)              is equivalent to r = a*b
    mul_hn_2p(a, b, r)               is equivalent to r += a*b
    mul_hn_2p(alpha, a, b, r)        is equivalent to r += alpha*a*b
    mul_hn_2p(alpha, a, b, beta, r ) is equivalent to r = beta*r+alpha*a*b

    @param a a boost::array of N simd vectors where N is the cardinal of an simd vector

    @param b a boost::array of P simd vectors

    @return a matrix of the same type as b
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mul_hn_2p_, mul_hn_2p, 2 )
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_hn_2p_, mul_hn_2p,(A0 const&)(A1 const&)(A2 &),3)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_hn_2p_, mul_hn_2p,(A0 const&)(A1 const&)(A2 const&)(A3 &),4)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mul_hn_2p_, mul_hn_2p,(A0 const&)(A1 const&)(A2 const&)(A3 const&)(A4 &),5)
} }



#endif
