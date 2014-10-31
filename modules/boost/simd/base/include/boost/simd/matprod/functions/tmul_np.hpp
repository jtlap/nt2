//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_TMUL_NP_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_TMUL_NP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief tmul_np generic tag

     Represents the tmul_np function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct tmul_np_ : ext::elementwise_<tmul_np_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tmul_np_> parent;
    };
  }
  /*!
    returns the matrix product of
          the transpose of an NxN matrix a represented by an array of N simd vector of cardinal N
       by an NxP matrix b represented by an array of P simd vector of cardinal N ( 0 < P and P static)

    simd vectors represent columns (lines of the transposed matrix)

    for sse2 this means 2x2 * 2xP  for double elements
                        4x4 * 4xP  for float elements
    for avx this means  4x4 * 4xP  for double elements
                        8x8 * 8xP  for float elements

    If * is an hypothetical matrix product between a and b, and alpha and beta are scalars

    r = tmul_np(a, b)              is equivalent to r = trans(a)*b
    tmul_np(a, b, r)               is equivalent to r += trans(a)*b
    tmul_np(alpha, a, b, r)        is equivalent to r += alpha*trans(a)*b
    tmul_np(alpha, a, b, beta, r ) is equivalent to r = beta*r+alpha*trans(a)*b

    @param a a boost::array of N simd vectors where N is the cardinal of an simd vector

    @param b a boost::array of P simd vectors

    @return a matrix of the same type as b
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tmul_np_, tmul_np, 2 )
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::tmul_np_, tmul_np,(A0 const&)(A1 const&)(A2 &),3)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::tmul_np_, tmul_np,(A0 const&)(A1 const&)(A2 const&)(A3 &),4)
  //@overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::tmul_np_, tmul_np,(A0 const&)(A1 const&)(A2 const&)(A3 const&)(A4 &),5)
} }



#endif
